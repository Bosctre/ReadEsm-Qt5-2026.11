#ifndef SPECIFICCONDITIONS_H
#define SPECIFICCONDITIONS_H

#include "../DataTypes/SpecificConditionRecord.h"
#include "../DataTypes/Subblocks.h"
#include "CardBlock.h"

class SpecificConditions : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(SpecificConditions)
public:
	
	Subblocks<SpecificConditionRecord> specificConditionRecords;

	SpecificConditions(const DataPointer& filewalker);
	///returns "SpecificConditions"
QString className() const;
	QString title() const;
	static const int Type = 0x0522;
	virtual void printOn(Reporter& report) const;
};


#endif
