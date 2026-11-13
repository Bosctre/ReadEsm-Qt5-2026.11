#ifndef CARDVEHICLESUSED_H
#define CARDVEHICLESUSED_H

#include "../DataTypes/Subblocks.h"
#include "../DataTypes/CardVehicleRecord.h"
#include "CardBlock.h"

class CardVehiclesUsed : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(CardVehiclesUsed)
public:
	
	int vehiclePointerNewestRecord;
	Subblocks<CardVehicleRecord> cardVehicleRecords;

	CardVehiclesUsed(const DataPointer& filewalker);
	///returns "CardVehiclesUsed"
QString className() const;
	QString title() const;
	static const int Type = 0x0505;
	virtual void printOn(Reporter& report) const;
};


#endif
