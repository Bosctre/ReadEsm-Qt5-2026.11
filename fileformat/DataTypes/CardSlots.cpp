#include "CardSlots.h"
#include "../Reporter/Reporter.h"
#include <QObject>


CardSlots::CardSlots(const DataPointer& filewalker)
    : RawCardSlots(filewalker)
{
}

void CardSlots::printOn(Reporter& report) const {
    if (cardNumberDriverSlotBegin != cardNumberDriverSlotEnd) {
        if (!cardNumberDriverSlotBegin.isDefaultValue())
            report.tagValuePair(QObject::tr("cardNumberDriverSlotBegin"), cardNumberDriverSlotBegin.toString());
        if (!cardNumberDriverSlotEnd.isDefaultValue())
            report.tagValuePair(QObject::tr("cardNumberDriverSlotEnd"), cardNumberDriverSlotEnd.toString());
    } else if (!cardNumberDriverSlotBegin.isDefaultValue()) {
        report.tagValuePair(QObject::tr("cardNumberDriverSlot"), cardNumberDriverSlotBegin.toString());
    }

    if (cardNumberCoDriverSlotBegin != cardNumberCoDriverSlotEnd) {
        if (!cardNumberCoDriverSlotBegin.isDefaultValue())
            report.tagValuePair(QObject::tr("cardNumberCoDriverSlotBegin"), cardNumberCoDriverSlotBegin.toString());
        if (!cardNumberCoDriverSlotEnd.isDefaultValue())
            report.tagValuePair(QObject::tr("cardNumberCoDriverSlotEnd"), cardNumberCoDriverSlotEnd.toString());
    } else if (!cardNumberCoDriverSlotBegin.isDefaultValue()) {
        report.tagValuePair(QObject::tr("cardNumberCoDriverSlot"), cardNumberCoDriverSlotBegin.toString());
    }
}

