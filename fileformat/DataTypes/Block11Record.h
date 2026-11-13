#ifndef BLOCK11RECORD_H
#define BLOCK11RECORD_H

#include "../DataTypes/Timespan.h"
#include "DataType.h"
#include "../DataTypes/FullCardNumber.h"
#include "../DataTypes/RawData.h"

/** in block 11, sometimesDuration seems to encode duration in seconds/3, in block 13 it seems to be seconds.*/
class Block11Record : public DataType {
	Q_DECLARE_TR_FUNCTIONS(Block11Record)
public:
	
	FullCardNumber cardNumber;
	Timespan time;
	int sometimesDuration;
	RawData payloadData;

	Block11Record(const DataPointer& filewalker);
	///returns "Block11Record"
QString className() const;
	int size() const;
	static const int staticSize = 58;
	virtual void printOn(Reporter& report) const;
};


#endif
