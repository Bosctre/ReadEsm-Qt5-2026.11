#ifndef CARDCONTROLACTIVITYDATARECORD_H
#define CARDCONTROLACTIVITYDATARECORD_H

#include "../DataTypes/VehicleRegistration.h"
#include "CardBlock.h"
#include "../DataTypes/Timespan.h"
#include "../DataTypes/TimeReal.h"
#include "../DataTypes/FullCardNumber.h"

class CardControlActivityDataRecord : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(CardControlActivityDataRecord)
public:
	
	int controlType;
	TimeReal controlTime;
	FullCardNumber controlCardNumber;
	VehicleRegistration controlVehicleRegistration;
	Timespan controlDownloadPeriod;

	CardControlActivityDataRecord(const DataPointer& filewalker);
	///returns "CardControlActivityDataRecord"
QString className() const;
	QString title() const;
	static const int Type = 0x0508;
	virtual void printOn(Reporter& report) const;
};


#endif
