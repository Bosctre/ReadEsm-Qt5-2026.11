

#include "CardPhoto.h"
#include "../Reporter/Reporter.h"
#include <QObject>


CardPhoto::CardPhoto(const DataPointer& start)
    : CardBlock(start)
{
}

QString CardPhoto::title() const {
    return QObject::tr("Card Photo");
}

void CardPhoto::printOn(Reporter& report) const {
    report.tagValuePair(QObject::tr("Card Photo"), title());
}

