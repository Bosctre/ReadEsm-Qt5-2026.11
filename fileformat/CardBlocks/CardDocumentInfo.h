#pragma once
#ifndef FILEFORMAT_CARDDOCUMENTINFO_H
#define FILEFORMAT_CARDDOCUMENTINFO_H

#include "CardBlock.h"


class CardDocumentInfo : public CardBlock {
public:
    explicit CardDocumentInfo(const DataPointer& start);

    QString title() const;
    void printOn(Reporter& report) const;
};

#endif
