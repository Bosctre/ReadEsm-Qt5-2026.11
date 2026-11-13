#ifndef CARDEVENTDATA_H
#define CARDEVENTDATA_H

#include "../DataTypes/Subblocks.h"
#include "CardBlock.h"
#include "../DataTypes/CardEventRecord.h"

class CardEventData : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(CardEventData)
public:
	
	Subblocks<CardEventRecord> cardEventRecords;

	CardEventData(const DataPointer& filewalker);
	///returns "CardEventData"
QString className() const;
	QString title() const;
	static const int Type = 0x0502;
	virtual void printOn(Reporter& report) const;
};


#endif
