#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include "../DataTypes/TimeReal.h"
#include "../DataTypes/Name.h"
#include "../DataTypes/BcdDate.h"
#include "CardBlock.h"

class Identification : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(Identification)
public:
	
	int cardIssuingMemberState;
	QString cardNumber;
	QString cardIssuingAuthorityName;
	TimeReal cardIssueDate;
	TimeReal cardValidityBegin;
	TimeReal cardExpiryDate;
	Name cardHolderName;
	BcdDate cardHolderBirthDate;
	QString cardHolderPreferredLanguage;

	Identification(const DataPointer& filewalker);
	///returns "Identification"
QString className() const;
	QString title() const;
	static const int Type = 0x0520;
	virtual void printOn(Reporter& report) const;
};


#endif
