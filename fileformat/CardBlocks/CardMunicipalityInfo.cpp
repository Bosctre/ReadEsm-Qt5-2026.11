#include "CardMunicipalityInfo.h"
#include "../Reporter/Reporter.h"
#include <QObject>


CardMunicipalityInfo::CardMunicipalityInfo(const DataPointer& start)
    : CardBlock(start)
{
}

QString CardMunicipalityInfo::title() const {
    return QObject::tr("Municipality Information");
}

void CardMunicipalityInfo::printOn(Reporter &report) const {
    report.tagValuePair(QObject::tr("Municipality Info"), title());
}

