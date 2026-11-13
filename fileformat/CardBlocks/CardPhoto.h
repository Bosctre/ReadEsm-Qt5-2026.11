#pragma once
#ifndef CARDPHOTO_H
#define CARDPHOTO_H

#include "CardBlock.h"


class Reporter;

class CardPhoto : public CardBlock {
public:
    explicit CardPhoto(const DataPointer& start);

    QString title() const override;
    void printOn(Reporter& report) const override;
};


#endif // CARDPHOTO_H

