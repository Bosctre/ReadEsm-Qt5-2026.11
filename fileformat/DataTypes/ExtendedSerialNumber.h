#ifndef EXTENDEDSERIALNUMBER_H
#define EXTENDEDSERIALNUMBER_H

#include "DataType.h"
#include "../DataTypes/BcdMonthYear.h"

class ExtendedSerialNumber : public DataType {
	Q_DECLARE_TR_FUNCTIONS(ExtendedSerialNumber)
public:
	
	int serialNumber;
	BcdMonthYear date;
	int equipmentType;
	int manufacturerCode;

	ExtendedSerialNumber(const DataPointer& filewalker);
	///returns "ExtendedSerialNumber"
QString className() const;
	int size() const;
	static const int staticSize = 8;
	QString toString() const;
	virtual void printOn(Reporter& report) const;
};


#endif
