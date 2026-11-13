#ifndef RAWCARDDRIVERACTIVITY_H
#define RAWCARDDRIVERACTIVITY_H

#include "../DataTypes/RawData.h"
#include "CardBlock.h"

class RawCardDriverActivity : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(CardDriverActivity)
public:
	
	int oldestRecord;
	int newestRecord;
	RawData cyclicData;

	RawCardDriverActivity(const DataPointer& filewalker);
	///returns "RawCardDriverActivity"
QString className() const;
	QString title() const;
	static const int Type = 0x0504;
	virtual void printOn(Reporter& report) const;
};


#endif
