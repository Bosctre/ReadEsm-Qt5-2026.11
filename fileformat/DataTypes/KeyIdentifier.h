#ifndef KEYIDENTIFIER_H
#define KEYIDENTIFIER_H

#include "DataType.h"
#include <QObject>
#include <QSharedPointer>


class KeyIdentifier : public DataType {
public:
    explicit KeyIdentifier(const DataPointer& start);

    QString className() const override;
    int size() const override;
    void printOn(Reporter& report) const override;
};


#endif // KEYIDENTIFIER_H