#ifndef DECRYPTEDCERTIFICATE_H
#define DECRYPTEDCERTIFICATE_H


#include "../DataTypes/RsaPublicKey.h"
#include "../DataTypes/KeyIdentifier.h"
#include "../DataTypes/TimeReal.h"
#include "../DataTypes/CertificateAuthority.h"
#include "DataType.h"
#include "../DataTypes/CertificateHolderAuthorization.h"

class DecryptedCertificate : public DataType {
	Q_DECLARE_TR_FUNCTIONS(DecryptedCertificate)
public:
	
	int certificateProfileIdentifier;
	CertificateAuthority certificateAuthorityReference;
	CertificateHolderAuthorization certificateHolderAuthorization;
	TimeReal endOfValidity;
	KeyIdentifier certificateHolderReference;
	RsaPublicKey rsaPublicKey;

	DecryptedCertificate(const DataPointer& filewalker);
	///returns "DecryptedCertificate"
QString className() const;
	int size() const;
	static const int staticSize = 164;
	virtual void printOn(Reporter& report) const;
};


#endif
