#ifndef TOPLEVELBLOCK_H
#define TOPLEVELBLOCK_H
#include "Block.h"
#include "Reporter/Reporter.h"
#include "DataPointer.h"
#include "readTypes.h"
#include "DataTypes/EncryptedCertificate.h"
#include "DataTypes/RawData.h"
#include <QString>


class TopLevelBlock : public Block {
public:
    TopLevelBlock(const DataPointer& start);
    virtual ~TopLevelBlock() = default;
    virtual int dataBlockSize() const = 0;
    virtual void checkSignature(const EncryptedCertificate& cert);
    virtual RawData signedBytes() const;
    virtual RawData signatureBytes() const;
    QString toString() const;
    QString title() const override;
    void printOn(Reporter& o) const override;
protected:
    DataPointer start;
    bool validSignature = false;
    bool hasSignature   = false;
};

#endif // TOPLEVELBLOCK_H
