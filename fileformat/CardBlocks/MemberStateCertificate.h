#ifndef MEMBERSTATECERTIFICATE_H
#define MEMBERSTATECERTIFICATE_H

#include "../DataTypes/EncryptedCertificate.h"
#include "CardBlock.h"

class MemberStateCertificate : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(MemberStateCertificate)
public:
	
	EncryptedCertificate certificate;

	MemberStateCertificate(const DataPointer& filewalker);
	///returns "MemberStateCertificate"
QString className() const;
	QString title() const;
	static const int Type = 0xc108;
	virtual void printOn(Reporter& report) const;
};


#endif
