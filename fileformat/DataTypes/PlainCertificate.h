#ifndef PLAINCERTIFICATE_H
#define PLAINCERTIFICATE_H

#include "../DataTypes/RsaPublicKey.h"
#include "DataType.h"
#include "../DataTypes/CertificateAuthority.h"

class PlainCertificate : public DataType {
	Q_DECLARE_TR_FUNCTIONS(PlainCertificate)
public:
	
	CertificateAuthority keyIdentifier;
	RsaPublicKey rsaPublicKey;

	PlainCertificate(const DataPointer& filewalker);
	///returns "PlainCertificate"
QString className() const;
	int size() const;
	static const int staticSize = 144;
	virtual void printOn(Reporter& report) const;
};


#endif
