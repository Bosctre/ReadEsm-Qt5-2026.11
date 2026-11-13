#include "RawFullCardNumber.h"
#include "../formatStrings.h"

RawFullCardNumber::RawFullCardNumber(const DataPointer& filewalker) : DataType(filewalker),
	cardType(readBigEndianInt1(start + 0 )),
	cardIssuingMemberState(readBigEndianInt1(start + 1 )),
	cardNumber(fixedString(start + 2 , 16))
{}

QString RawFullCardNumber::className() const {
	return "RawFullCardNumber";
}

int RawFullCardNumber::size() const{
	return 18 ;
}

QString RawFullCardNumber::toString() const{
	return QString();
}

void RawFullCardNumber::printOn(Reporter& report) const {
	report.tagValuePair(tr("cardType"), formatStrings::equipmentType(cardType));
	report.tagValuePair(tr("cardIssuingMemberState"), formatStrings::nationNumeric(cardIssuingMemberState));
	report.tagValuePair(tr("cardNumber"), cardNumber);
}
