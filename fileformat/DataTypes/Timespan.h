#ifndef TIMESPAN_H
#define TIMESPAN_H

#include "DataType.h"
#include "TimeReal.h"

class Timespan : public DataType {
public:
    Timespan(DataPointer start);
    int size() const { return 8; }
    QString toString() const override;
    QString className() const override { return QStringLiteral("Timespan"); }
    void printOn(Reporter& report) const override;

    TimeReal begin;
    TimeReal end;
};

#endif