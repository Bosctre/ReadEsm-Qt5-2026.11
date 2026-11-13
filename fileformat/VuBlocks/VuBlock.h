#ifndef VUBLOCK_H
#define VUBLOCK_H

#include "../TopLevelBlock.h"
#include "../DataTypes/RawData.h"

class VuBlock : public TopLevelBlock {
public:
    VuBlock(const DataPointer& nstart);
    virtual ~VuBlock() = default;

    int dataBlockSize() const override { return size() - 2 - (hasSignature ? 128 : 0); }

    virtual QString title() const override = 0;
    virtual int size() const = 0;
    virtual void printOn(Reporter& report) const override = 0;

    RawData signedBytes() const override;
    RawData signatureBytes() const override;
};

#endif // VUBLOCK_H