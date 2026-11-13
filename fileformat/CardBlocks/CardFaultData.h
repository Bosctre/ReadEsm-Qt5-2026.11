#ifndef CARDFAULTDATA_H
#define CARDFAULTDATA_H

#include "../DataTypes/Subblocks.h"
#include "CardBlock.h"
#include "../DataTypes/CardEventRecord.h"

class CardFaultData : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(CardFaultData)
public:
	
	Subblocks<CardEventRecord> cardFaultRecords;

	CardFaultData(const DataPointer& filewalker);
	///returns "CardFaultData"
QString className() const;
	QString title() const;
	static const int Type = 0x0503;
	virtual void printOn(Reporter& report) const;
};


#endif
