#include "ConcreteRawData.h"
#include "../Reporter/Reporter.h"
#include "../readTypes.h"


ConcreteRawData::ConcreteRawData(const DataPointer& s)
    : CardBlock(s) {}

int ConcreteRawData::size() const {
    if (start.bytesLeft() < 4) return start.bytesLeft();
    int length = readBigEndianInt2(start + 2);
    return 4 + length;
}

void ConcreteRawData::printOn(Reporter& report) const {
    report.tagValuePair(tr("Raw Data"), QString("(%1 bytes)").arg(size()));
}

DataPointer ConcreteRawData::payload() const {
    return start;
}

