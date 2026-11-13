#ifndef SPECIFICCONDITIONRECORD_H
#define SPECIFICCONDITIONRECORD_H

#include "DataType.h"
#include "../DataTypes/TimeReal.h"

class SpecificConditionRecord : public DataType {
	Q_DECLARE_TR_FUNCTIONS(SpecificConditionRecord)
public:
	
	TimeReal entryTime;
	int specificConditionType;

	SpecificConditionRecord(const DataPointer& filewalker);
	///returns "SpecificConditionRecord"

bool isEmpty() const override {
    const char* p = start.getData();
    if (!p) return true;
    for (int i = 0; i < 5; ++i) if (p[i] != 0) return false;   // heure (4) + type (1)
    return true;
}

QString className() const;
	int size() const;
	static const int staticSize = 5;
	virtual void printOn(Reporter& report) const;
};


#endif
