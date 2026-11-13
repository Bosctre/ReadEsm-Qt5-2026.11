#ifndef PLACERECORD_H
#define PLACERECORD_H

#include "DataType.h"
#include "../DataTypes/TimeReal.h"

class PlaceRecord : public DataType {
	Q_DECLARE_TR_FUNCTIONS(PlaceRecord)
public:
	
	TimeReal entryTime;
	int entryTypeDailyWorkPeriod;
	int dailyWorkPeriodCountry;
	int dailyWorkPeriodRegion;
	int vehicleOdometerValue;

	PlaceRecord(const DataPointer& filewalker);
	///returns "PlaceRecord"
QString className() const;
	int size() const;
	static const int staticSize = 10;
	QString toString() const;
	virtual void printOn(Reporter& report) const;
};


#endif
