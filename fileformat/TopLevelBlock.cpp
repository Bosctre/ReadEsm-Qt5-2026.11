#include "TopLevelBlock.h"
#include <QObject>
#include <QDebug>


TopLevelBlock::TopLevelBlock(const DataPointer& s)
    : start(s)
{}

RawData TopLevelBlock::signedBytes() const {
    // Les octets signés sont ceux du bloc de données
    return RawData(start, dataBlockSize());
}

RawData TopLevelBlock::signatureBytes() const {
    // La signature (128 octets) suit immédiatement le bloc de données
    return RawData(start + dataBlockSize(), 128);
}

void TopLevelBlock::checkSignature(const EncryptedCertificate& cert) {
#ifdef HAVE_CRYPTO
    if (hasSignature)
        validSignature = cert.checkSignature(signedBytes(), signatureBytes());
    qDebug() << title() << (validSignature ? "Signature OK" : "Signature FAIL");
#endif
}

QString TopLevelBlock::toString() const {
    return "TopLevelBlock";
}

QString TopLevelBlock::title() const {
    return QObject::tr("Unknown block type 0x%1")
        .arg(readBigEndianInt2(start), 4, 16, QChar('0'));
}

void TopLevelBlock::printOn(Reporter& o) const {
    o.tagValuePair(QObject::tr("length"), QString::number(dataBlockSize()));
}

