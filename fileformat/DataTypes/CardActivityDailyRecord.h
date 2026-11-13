#ifndef CARDACTIVITYDAILYRECORD_H
#define CARDACTIVITYDAILYRECORD_H

#include "RawCardActivityDailyRecord.h"
#include "../DataTypes/ActivityChangeInfo.h"
#include "../PictureGenerators/SvgDayActivity.h"
#include "../PictureGenerators/ActivityDrawing.h"
#include <vector>

class CardActivityDailyRecord : public RawCardActivityDailyRecord {
public:
    CardActivityDailyRecord(const DataPointer& filewalker);

    QString className() const override;
    void printOn(Reporter& report) const override;

    /// Conduite / travail / repos / disponibilité de la journée, en minutes
    ActivityDrawing::DayTotals totals() const { return ActivityDrawing::totals(activities); }

private:
    std::vector<ActivityChangeInfo> activities;
};

#endif // CARDACTIVITYDAILYRECORD_H
