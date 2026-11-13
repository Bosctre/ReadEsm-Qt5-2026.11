#pragma once
#ifndef CARDMUNICIPALITYINFO_H
#define CARDMUNICIPALITYINFO_H

#include "CardBlock.h"
#include <QString>


class Reporter;

class CardMunicipalityInfo : public CardBlock {
public:
    explicit CardMunicipalityInfo(const DataPointer& start);

    QString title() const;
    void printOn(Reporter& report) const;
};


#endif // CARDMUNICIPALITYINFO_H

