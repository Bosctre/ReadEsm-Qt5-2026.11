#include "CardValidity.h"
#include "../Reporter/Reporter.h"
#include <QObject>


CardValidity::CardValidity(const DataPointer& start)
   : CardBlock(start)
{
}

QString CardValidity::title() const {
    return QObject::tr("Document Validity");
}

void CardValidity::printOn(Reporter &report) const {
   report.tagValuePair(QObject::tr("Document Validity"), title());
}


