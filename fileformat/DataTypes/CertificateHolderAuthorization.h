#ifndef CERTIFICATEHOLDERAUTHORIZATION_H
#define CERTIFICATEHOLDERAUTHORIZATION_H

#include "DataType.h"
#include "../DataTypes/RawData.h"

class CertificateHolderAuthorization : public DataType {
	Q_DECLARE_TR_FUNCTIONS(CertificateHolderAuthorization)
public:
	
	RawData tachographApplicationId;
	int equipmentType;

	CertificateHolderAuthorization(const DataPointer& filewalker);
	///returns "CertificateHolderAuthorization"
QString className() const;
	int size() const;
	static const int staticSize = 7;
	virtual void printOn(Reporter& report) const;
};


#endif
