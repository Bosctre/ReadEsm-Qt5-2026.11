#ifndef RAWDATA_H
#define RAWDATA_H

#include <QString>
#include <QByteArray>
#include "DataType.h"
#include "../DataPointer.h"

class RawData : public DataType {
public:
    /// Longueur explicite (utilisé par le code généré et les blocs)
    RawData(const DataPointer& start, int length);

    /// Jusqu'à la fin des données disponibles (blocs inconnus)
    explicit RawData(const DataPointer& start);

    const char* data() const;
    unsigned char operator[](int i) const;

    QString className() const override;
    int size() const override;
    void printOn(Reporter& report) const override;
    QString toString() const;

private:
    int length;
};

#endif // RAWDATA_H