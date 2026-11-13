#ifndef CARDEVENTRECORD_H
#define CARDEVENTRECORD_H

#include "../DataTypes/Timespan.h"
#include "DataType.h"
#include "../DataTypes/VehicleRegistration.h"

class CardEventRecord : public DataType {
	Q_DECLARE_TR_FUNCTIONS(CardEventRecord)
public:
	
	int eventType;
	Timespan eventTime;
	VehicleRegistration eventVehicleRegistration;

/// Emplacement jamais écrit : type + début + fin à zéro (9 premiers octets)
bool isEmpty() const override {
    const char* p = start.getData();
    if (!p) return true;
    for (int i = 0; i < 9; ++i) if (p[i] != 0) return false;   // type + début + fin
    return true;
}

	CardEventRecord(const DataPointer& filewalker);
	///returns "CardEventRecord"
QString className() const;
	int size() const;
	static const int staticSize = 24;
	virtual void printOn(Reporter& report) const;
};


#endif
