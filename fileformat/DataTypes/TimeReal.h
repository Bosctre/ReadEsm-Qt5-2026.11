#ifndef FILEFORMAT_TIMEREAL_H
#define FILEFORMAT_TIMEREAL_H

#include <QDateTime>
#include "DataType.h"
#include "../DataPointer.h"

/// Date et heure : secondes depuis le 1er janvier 1970, UTC (4 octets, big-endian)
class TimeReal : public DataType {
public:
    explicit TimeReal(const DataPointer& start);

    QString className() const override;
    int size() const override;
    void printOn(Reporter& report) const override;

    QString toString() const override;      // date + heure
    QString dateString() const;             // date seule
    QDateTime toDateTime() const;
    quint32 seconds() const { return secs; }

private:
    quint32 secs;
};

#endif // FILEFORMAT_TIMEREAL_H