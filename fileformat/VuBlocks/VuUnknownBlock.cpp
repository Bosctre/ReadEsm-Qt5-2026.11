#include "VuUnknownBlock.h"
#include "../Reporter/Reporter.h"


VuUnknownBlock::VuUnknownBlock(const DataPointer& s)
    : VuBlock(s), data(s)
{
    hasSignature = false;
}

int VuUnknownBlock::dataBlockSize() const { return size(); }

int VuUnknownBlock::size() const {
    return start.bytesLeft();
}

QString VuUnknownBlock::title() const {
    return tr("Unknown Vu block, TREP 0x%1").arg(start[1], 2, 16, QChar('0'));
}

QString VuUnknownBlock::className() const {
    return QString("VuUnknownBlock%1").arg(start[1], 2, 16, QChar('0'));
}

void VuUnknownBlock::printOn(Reporter& o) const {
    o.tagValuePair(tr("Raw Data"), QString("(%1 bytes)").arg(dataBlockSize()));
}

