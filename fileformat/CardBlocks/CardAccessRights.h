#ifndef CARDACCESSRIGHTS_H
#define CARDACCESSRIGHTS_H

#include "../DataTypes/DataType.h"
#include "../DataPointer.h"


class CardAccessRights : public DataType {
public:
    CardAccessRights(const DataPointer& start);

    QString className() const override;
    int size() const override;
    void printOn(Reporter& report) const override;

private:
    DataPointer m_start;
};


#endif // CARDACCESSRIGHTS_H
