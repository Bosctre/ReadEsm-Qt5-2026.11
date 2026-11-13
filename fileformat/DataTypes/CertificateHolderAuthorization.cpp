#include "CertificateHolderAuthorization.h"

#include "../formatStrings.h"

CertificateHolderAuthorization::CertificateHolderAuthorization(const DataPointer& filewalker) : DataType(filewalker),
	tachographApplicationId(start + 0 , 6),
	equipmentType(readBigEndianInt1(start + 6 ))
{}

QString CertificateHolderAuthorization::className() const {
	return "CertificateHolderAuthorization";
}

int CertificateHolderAuthorization::size() const{
	return 7 ;
}

void CertificateHolderAuthorization::printOn(Reporter& report) const {
	report.tagValuePair(tr("tachographApplicationId"), tachographApplicationId.toString());
	report.tagValuePair(tr("equipmentType"), formatStrings::equipmentType(equipmentType));
}

