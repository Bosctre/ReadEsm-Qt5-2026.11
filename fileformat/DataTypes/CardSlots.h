#ifndef CARDSLOTS_H
#define CARDSLOTS_H
#include "RawCardSlots.h"


class CardSlots : public RawCardSlots {
public:
    explicit CardSlots(const DataPointer& filewalker);
    void printOn(Reporter& report) const override;
};

#endif // CARDSLOTS_H
