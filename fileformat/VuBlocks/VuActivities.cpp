#include "VuActivities.h"
#include "../Reporter/Reporter.h"
#include "../PictureGenerators/SvgDayActivity.h"
#include "../PictureGenerators/ActivityDrawing.h"
#include <QDateTime>

VuActivities::VuActivities(const DataPointer& filewalker) : RawVuActivities(filewalker) {}

QString VuActivities::title() const {
    return tr("Activities on %1").arg(timeReal.toString());
}

void VuActivities::printOn(Reporter& report) const {
    report.tagValuePair(tr("timeReal"), timeReal.toString());
    report.tagValuePair(tr("odometerValueMidnight"), QString("%1 km").arg(odometerValueMidnight));

    SvgDayActivity svg;
    ActivityDrawing::drawDay(svg, activityChangeInfos.getSubblocks());
    report.tagValuePair(tr("Visualization"), svg.toString());

    report.writeArray(vuCardIWRecords, tr("vuCardIWRecords"), false);
    report.writeArray(activityChangeInfos, tr("activityChangeInfos"), false);
    report.writeArray(vuPlaceDailyWorkPeriodRecords, tr("vuPlaceDailyWorkPeriodRecords"), false);
    report.writeArray(specificConditionRecords, tr("specificConditionRecords"), false);
}