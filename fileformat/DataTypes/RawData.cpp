#include "RawData.h"
#include "../Reporter/Reporter.h"
#include <QObject>

RawData::RawData(const DataPointer& s, int len) : DataType(s), length(len) {}

RawData::RawData(const DataPointer& s) : DataType(s), length(s.bytesLeft()) {}

const char* RawData::data() const {
    return start.getData();
}

unsigned char RawData::operator[](int i) const {
    if (i < 0 || i >= length) return 0;
    return static_cast<unsigned char>(data()[i]);
}

int RawData::size() const {
    return length;
}

QString RawData::className() const {
    return "RawData";
}

QString RawData::toString() const {
    return QString::fromLatin1(QByteArray(data(), length).toHex(' '));
}

void RawData::printOn(Reporter& report) const {
    report.tagValuePair(QObject::tr("Data"), toString());
}