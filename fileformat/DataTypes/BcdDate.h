#ifndef BCDDATE_H
#define BCDDATE_H

#include "DataType.h"
#include "../DataTypes/RawData.h"

class BcdDate : public DataType {
	Q_DECLARE_TR_FUNCTIONS(BcdDate)
public:
	
	RawData encodedDate;

	BcdDate(const DataPointer& filewalker);
	///returns "BcdDate"
QString className() const;
	int size() const;
	static const int staticSize = 4;
	QString toString() const;
	virtual void printOn(Reporter& report) const;
};


#endif
