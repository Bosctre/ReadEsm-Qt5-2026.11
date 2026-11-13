#include "CardHeader.h"
#include "../Reporter/Reporter.h"
#include <QObject>


CardHeader::CardHeader(const DataPointer& start) : DataType(start), m_start(start) {
    if (start.isValid() && start.bytesLeft() >= 19) {
        headerBytes = QByteArray(start.getData(), 19);
    }
}

QString CardHeader::className() const {
    return "CardHeader";
}

int CardHeader::size() const {
    return 19;
}

QString CardHeader::title() const {
    return QObject::tr("Card Header");
}

void CardHeader::printOn(Reporter& report) const {
    report.tagValuePair(QObject::tr("Card Header"), title());
    report.tagValuePair(QObject::tr("Header Bytes"), QString::fromLatin1(headerBytes.toHex(' ')));
}

