#ifndef CARDDRIVINGLICENSEINFORMATION_H
#define CARDDRIVINGLICENSEINFORMATION_H

#include "CardBlock.h"

class CardDrivingLicenseInformation : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(CardDrivingLicenseInformation)
public:
	
	QString drivingLicenseIssuingAuthorithy;
	int drivingLicenseIssuingNation;
	QString drivingLicenseNumber;

	CardDrivingLicenseInformation(const DataPointer& filewalker);
	///returns "CardDrivingLicenseInformation"
QString className() const;
	QString title() const;
	static const int Type = 0x0521;
	virtual void printOn(Reporter& report) const;
};


#endif
