#include "CertificateAuthority.h"

#include "../formatStrings.h"

CertificateAuthority::CertificateAuthority(const DataPointer& filewalker) : DataType(filewalker),
	nationNumeric(readBigEndianInt1(start + 0 )),
	nationAlpha(fixedString(start + 1 , 3)),
	keySerialNumber(readBigEndianInt1(start + 4 )),
	additionalInfo(start + 5 , 2),
	caIdentifer(readBigEndianInt1(start + 7 ))
{}

QString CertificateAuthority::className() const {
	return "CertificateAuthority";
}

int CertificateAuthority::size() const{
	return 8 ;
}

void CertificateAuthority::printOn(Reporter& report) const {
	report.tagValuePair(tr("nationNumeric"), formatStrings::nationNumeric(nationNumeric));
	report.tagValuePair(tr("nationAlpha"), nationAlpha);
	report.tagValuePair(tr("keySerialNumber"), keySerialNumber);
	report.tagValuePair(tr("additionalInfo"), additionalInfo.toString());
	report.tagValuePair(tr("caIdentifer"), caIdentifer);
}

