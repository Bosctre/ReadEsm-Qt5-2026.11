#pragma once
#ifndef CARDVALIDITY_H
#define CARDVALIDITY_H

#include "CardBlock.h"
#include <QString>


class Reporter;

class CardValidity : public CardBlock {
public:
    explicit CardValidity(const DataPointer& start);

    QString title() const;
    void printOn(Reporter& report) const;
};


#endif // CARDVALIDITY_H
