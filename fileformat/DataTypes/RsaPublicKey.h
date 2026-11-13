#ifndef RSAPUBLICKEY_H
#define RSAPUBLICKEY_H
#include "RawRsaPublicKey.h"
#include "RawData.h"
#include <QByteArray>
#include "LargeNumber.h"



class RsaPublicKey : public RawRsaPublicKey {
public:
    explicit RsaPublicKey(const DataPointer& start);
    QString className() const override;
    int size() const override;
    void printOn(Reporter& report) const override;
    QByteArray perform(const RawData& input) const;
};

#endif // RSAPUBLICKEY_H
