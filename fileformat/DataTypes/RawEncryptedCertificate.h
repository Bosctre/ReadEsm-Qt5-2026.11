#ifndef RAWENCRYPTEDCERTIFICATE_H
#define RAWENCRYPTEDCERTIFICATE_H

#include "DataType.h"
#include "../DataTypes/RawData.h"
#include "../DataTypes/CertificateAuthority.h"

class RawEncryptedCertificate : public DataType {
	Q_DECLARE_TR_FUNCTIONS(EncryptedCertificate)
public:
	
	RawData sign;
	RawData cndash;
	CertificateAuthority certificateAuthorityReference;

	RawEncryptedCertificate(const DataPointer& filewalker);
	///returns "RawEncryptedCertificate"
QString className() const;
	int size() const;
	static const int staticSize = 194;
	virtual void printOn(Reporter& report) const;
};


#endif
