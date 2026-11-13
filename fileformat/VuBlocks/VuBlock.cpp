#include "VuBlock.h"


VuBlock::VuBlock(const DataPointer& nstart)
    : TopLevelBlock(nstart)
{
    hasSignature = true;
}

RawData VuBlock::signedBytes() const {
    // Données du bloc, sans les 2 octets d'en-tête (0x76 + TREP)
    return RawData(start + 2, dataBlockSize());
}

RawData VuBlock::signatureBytes() const {
    // La signature (128 octets) suit les données
    return RawData(start + 2 + dataBlockSize(), 128);
}