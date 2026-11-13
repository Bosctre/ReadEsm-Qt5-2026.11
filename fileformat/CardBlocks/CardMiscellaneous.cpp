#include "CardMiscellaneous.h"
#include "../Reporter/Reporter.h"


CardMiscellaneous::CardMiscellaneous(const DataPointer& dp)
    : CardBlock(dp)
{
}

QString CardMiscellaneous::title() const
{
    return QStringLiteral("Card Miscellaneous");
}

void CardMiscellaneous::printOn(Reporter& report) const
{
    report.tagValuePair(QStringLiteral("Card Miscellaneous"), title());
}


