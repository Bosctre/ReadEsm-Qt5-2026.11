#pragma once
#include <QCoreApplication>
#ifndef CONCRETERAWDATA_H
#define CONCRETERAWDATA_H
#include "../CardBlocks/CardBlock.h"


class ConcreteRawData : public CardBlock {
    Q_DECLARE_TR_FUNCTIONS(ConcreteRawData)
public:
    explicit ConcreteRawData(const DataPointer& start);
    QString className() const override { return "RawData"; }
    int size() const override;
    void printOn(Reporter& report) const override;
    DataPointer payload() const override;
};

#endif // CONCRETERAWDATA_H
