#pragma once
#ifndef CARDISSUERINFO_H
#define CARDISSUERINFO_H

#include "CardBlock.h"
#include <QString>


class Reporter;

class CardIssuerInfo : public CardBlock {
public:
    explicit CardIssuerInfo(const DataPointer& dp);

    QString title() const;
    void printOn(Reporter& report) const;
};


#endif // CARDISSUERINFO_H

