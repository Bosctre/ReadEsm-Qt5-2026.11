#include "../DataTypes/CardActivityDailyRecord.h"
#include "../DataPointer.h"
#include "../Reporter/Reporter.h"
#include "../readTypes.h"
#include "../DataTypes/ActivityChangeDetail.h"
#include "../PictureGenerators/SvgDayActivity.h"
#include "../PictureGenerators/ActivityDrawing.h"
#include <QObject>
#include <QCoreApplication>
#include <algorithm>

CardActivityDailyRecord::CardActivityDailyRecord(const DataPointer& filewalker)
    : RawCardActivityDailyRecord(filewalker)
{
    // Chaque ActivityChangeInfo fait 2 octets, après l'en-tête de staticSize octets
    const DataPointer activityPtr = filewalker + staticSize;
    const int payload = std::min<int>(activityRecordLength - staticSize, activityPtr.bytesLeft());

    for (int offset = 0; offset + 2 <= payload; offset += 2)
        activities.push_back(ActivityChangeInfo(activityPtr + offset));
}

QString CardActivityDailyRecord::className() const {
    return "CardActivityDailyRecord";
}

void CardActivityDailyRecord::printOn(Reporter& report) const {
    RawCardActivityDailyRecord::printOn(report);

    SvgDayActivity svg;
    ActivityDrawing::drawDay(svg, activities);
    report.tagValuePair(QCoreApplication::translate("CardActivityDailyRecord", "Visualization"), svg.toString());

    const int n = int(activities.size());
    if (n > 0) {
        report.beginList(QCoreApplication::translate("CardActivityDailyRecord", "activityChangeInfos"), n, false);   // replié « (show) »
        for (int i = 0; i < n; ++i) {
            const int to = (i + 1 < n) ? activities[i + 1].getMinutes() : 1440;
            ActivityChangeDetail d(start, activities[i], to);
            report.writeBlock(d, d.title());
        }
        report.endList();
    }
}