#pragma once
#ifndef CARDMISCELLANEOUS_H
#define CARDMISCELLANEOUS_H

#include "CardBlock.h"
#include <QString>


class Reporter;

class CardMiscellaneous : public CardBlock {
public:
    explicit CardMiscellaneous(const DataPointer& dp);

    QString title() const;
    void printOn(Reporter& report) const;
};


#endif // CARDMISCELLANEOUS_H
