#include "BcdMonthYear.h"


BcdMonthYear::BcdMonthYear(const DataPointer& filewalker) : DataType(filewalker),
	encodedDate(start + 0 , 2)
{}

QString BcdMonthYear::className() const {
	return "BcdMonthYear";
}

int BcdMonthYear::size() const{
	return 2 ;
}

QString BcdMonthYear::toString() const{
	return "20" + bcdbyte(encodedDate[1]) + "-" + bcdbyte(encodedDate[0]);
}

void BcdMonthYear::printOn(Reporter& report) const {
	report.tagValuePair(tr("encodedDate"), encodedDate.toString());
}

