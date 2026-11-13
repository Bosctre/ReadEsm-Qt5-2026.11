#include "CardDocumentInfo.h"


CardDocumentInfo::CardDocumentInfo(const DataPointer& start)
    : CardBlock(start)
{
}

QString CardDocumentInfo::title() const {
    return "Card Document Info";
}

void CardDocumentInfo::printOn(Reporter&) const {
    // pas encore de rendu
}

