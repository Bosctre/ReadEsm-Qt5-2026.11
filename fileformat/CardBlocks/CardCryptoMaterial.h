
#pragma once
#ifndef FILEFORMAT_CARDCRYPTOMATERIAL_H
#define FILEFORMAT_CARDCRYPTOMATERIAL_H

#include "CardBlock.h"

class CardCryptoMaterial : public CardBlock {
public:
    explicit CardCryptoMaterial(const DataPointer& start);

    QString title() const;
    void printOn(Reporter& report) const;
};

#endif
