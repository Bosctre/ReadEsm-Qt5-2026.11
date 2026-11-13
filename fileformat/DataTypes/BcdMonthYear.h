#ifndef BCDMONTHYEAR_H
#define BCDMONTHYEAR_H

#include "DataType.h"
#include "../DataTypes/RawData.h"

class BcdMonthYear : public DataType {
	Q_DECLARE_TR_FUNCTIONS(BcdMonthYear)
public:
	
	RawData encodedDate;

	BcdMonthYear(const DataPointer& filewalker);
	///returns "BcdMonthYear"
QString className() const;
	int size() const;
	static const int staticSize = 2;
	QString toString() const;
	virtual void printOn(Reporter& report) const;
};


#endif
