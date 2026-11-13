#ifndef RAWCARDACTIVITYDAILYRECORD_H
#define RAWCARDACTIVITYDAILYRECORD_H

#include "DataType.h"
#include "../DataTypes/TimeReal.h"

class RawCardActivityDailyRecord : public DataType {
	Q_DECLARE_TR_FUNCTIONS(CardActivityDailyRecord)
public:
	
	int activityRecordPreviousLength;
	int activityRecordLength;
	TimeReal activityRecordDate;
	int activityPresenceCounter;
	int activityDayDistance;

	RawCardActivityDailyRecord(const DataPointer& filewalker);
	///returns "RawCardActivityDailyRecord"
QString className() const;
	QString title() const;
	int size() const;
	static const int staticSize = 12;
	virtual void printOn(Reporter& report) const;
};


#endif
