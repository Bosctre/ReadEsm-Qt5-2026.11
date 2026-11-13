#include "CardIssuerInfo.h"
#include "../Reporter/Reporter.h"


CardIssuerInfo::CardIssuerInfo(const DataPointer& dp)
    : CardBlock(dp)
{
}

QString CardIssuerInfo::title() const
{
    return QStringLiteral("Card Issuer Information");
}

void CardIssuerInfo::printOn(Reporter& report) const
{
    report.tagValuePair(QStringLiteral("Card Issuer Info"), title());
}

