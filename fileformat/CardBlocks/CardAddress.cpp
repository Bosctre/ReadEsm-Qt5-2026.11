#include "CardAddress.h"
#include "../Reporter/Reporter.h"
#include <QObject>


CardAddress::CardAddress(const DataPointer& start) : DataType(start), m_start(start) {}

QString CardAddress::className() const {
    return "CardAddress";
}

int CardAddress::size() const {
    return m_start.bytesLeft();
}

QString CardAddress::title() const {
    return QObject::tr("Card Address");
}

void CardAddress::printOn(Reporter& report) const {
    report.tagValuePair(QObject::tr("Payload size"), QString("%1 bytes").arg(m_start.bytesLeft()));
}

