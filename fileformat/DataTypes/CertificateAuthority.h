#ifndef CERTIFICATEAUTHORITY_H
#define CERTIFICATEAUTHORITY_H

#include "DataType.h"
#include "../DataTypes/RawData.h"

class CertificateAuthority : public DataType {
	Q_DECLARE_TR_FUNCTIONS(CertificateAuthority)
public:
	
	int nationNumeric;
	QString nationAlpha;
	int keySerialNumber;
	RawData additionalInfo;
	int caIdentifer;

	CertificateAuthority(const DataPointer& filewalker);
	///returns "CertificateAuthority"
QString className() const;
	int size() const;
	static const int staticSize = 8;
	virtual void printOn(Reporter& report) const;
};


#endif
