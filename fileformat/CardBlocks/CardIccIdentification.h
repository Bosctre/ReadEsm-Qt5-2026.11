#ifndef CARDICCIDENTIFICATION_H
#define CARDICCIDENTIFICATION_H

#include "../DataTypes/RawData.h"
#include "CardBlock.h"
#include "../DataTypes/ExtendedSerialNumber.h"

class CardIccIdentification : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(CardIccIdentification)
public:
	
	int clockStop;
	ExtendedSerialNumber cardExtendedSerialNumber;
	RawData cardApprovalNumber;
	RawData cardPersonaliserID;
	RawData embedderIcAssemblerId;
	RawData icIdentifier;

	CardIccIdentification(const DataPointer& filewalker);
	///returns "CardIccIdentification"
QString className() const;
	QString title() const;
	static const int Type = 0x0002;
	virtual void printOn(Reporter& report) const;
};


#endif
