#ifndef CARDPLACEDAILYWORKPERIOD_H
#define CARDPLACEDAILYWORKPERIOD_H

#include "../DataTypes/Subblocks.h"
#include "../DataTypes/PlaceRecord.h"
#include "CardBlock.h"

class CardPlaceDailyWorkPeriod : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(CardPlaceDailyWorkPeriod)
public:
	
	int placePointerNewestRecord;
	Subblocks<PlaceRecord> placeRecords;

	CardPlaceDailyWorkPeriod(const DataPointer& filewalker);
	///returns "CardPlaceDailyWorkPeriod"
QString className() const;
	QString title() const;
	static const int Type = 0x0506;
	virtual void printOn(Reporter& report) const;
};


#endif
