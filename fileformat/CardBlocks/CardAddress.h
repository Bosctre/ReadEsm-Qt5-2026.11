#ifndef CARDADDRESS_H
#define CARDADDRESS_H

#include "../DataTypes/DataType.h"
#include "../DataPointer.h"


class CardAddress : public DataType {
public:
    CardAddress(const DataPointer& start);

    QString className() const override;
    int size() const override;
    QString title() const;
    void printOn(Reporter& report) const override;

private:
    DataPointer m_start;
};


#endif // CARDADDRESS_H

