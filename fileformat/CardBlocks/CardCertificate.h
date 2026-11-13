#ifndef CARDCERTIFICATE_H
#define CARDCERTIFICATE_H

#include "../DataTypes/EncryptedCertificate.h"
#include "CardBlock.h"

class CardCertificate : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(CardCertificate)
public:
	
	EncryptedCertificate certificate;

	CardCertificate(const DataPointer& filewalker);
	///returns "CardCertificate"
QString className() const;
	QString title() const;
	static const int Type = 0xc100;
	virtual void printOn(Reporter& report) const;
};


#endif
