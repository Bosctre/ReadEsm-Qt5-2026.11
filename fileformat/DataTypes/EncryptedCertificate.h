#ifndef ENCRYPTEDCERTIFICATE_H
#define ENCRYPTEDCERTIFICATE_H

#include "DataType.h"
#include <QSharedPointer>


class EncryptedCertificate : public DataType {
public:
    explicit EncryptedCertificate(const DataPointer& filewalker);

    QString className() const override;
    int size() const override;
    void printOn(Reporter& report) const override;
};


#endif // ENCRYPTEDCERTIFICATE_H

