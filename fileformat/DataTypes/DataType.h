#ifndef DATATYPE_H
#define DATATYPE_H

#include "../DataPointer.h"
#include "../readTypes.h"
#include "../Reporter/Reporter.h"
#include <QString>


class DataType {
public:
    DataType(const DataPointer& start);
    virtual ~DataType() = default;
    virtual bool isEmpty() const { return false; }
    virtual QString className() const = 0;
    virtual int size() const = 0;
    virtual void printOn(Reporter& report) const = 0;
    virtual QString toString() const;

protected:
    DataPointer start;
};


#endif // DATATYPE_H