#include "CardCryptoMaterial.h"


CardCryptoMaterial::CardCryptoMaterial(const DataPointer& start)
    : CardBlock(start)
{
}

QString CardCryptoMaterial::title() const {
    return "Card Crypto Material";
}

void CardCryptoMaterial::printOn(Reporter&) const {
    // volontairement vide
}

