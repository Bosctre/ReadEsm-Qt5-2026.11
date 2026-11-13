#ifndef RAWCARDSLOTS_H
#define RAWCARDSLOTS_H

#include "DataType.h"
#include "../DataTypes/FullCardNumber.h"

class RawCardSlots : public DataType {
	Q_DECLARE_TR_FUNCTIONS(CardSlots)
public:
	
	FullCardNumber cardNumberDriverSlotBegin;
	FullCardNumber cardNumberCoDriverSlotBegin;
	FullCardNumber cardNumberDriverSlotEnd;
	FullCardNumber cardNumberCoDriverSlotEnd;

	RawCardSlots(const DataPointer& filewalker);
	///returns "RawCardSlots"
QString className() const;
	int size() const;
	static const int staticSize = 72;
	virtual void printOn(Reporter& report) const;
};


#endif
