#pragma once
#ifndef FILEFORMAT_DATAPOINTERTIME_H
#define FILEFORMAT_DATAPOINTERTIME_H

#include "../DataPointer.h"
#include <QDateTime>
#include <QString>


class DataPointerTime {
public:
    DataPointerTime();
    explicit DataPointerTime(const DataPointer& ptr); // lit 4 bytes BE -> minutes since epoch defined below

    bool isValid() const;

    QDate date() const;
    QTime time() const;
    QString toString() const;

    int secsTo(const DataPointerTime& other) const;

    bool operator==(const DataPointerTime& other) const;

private:
    bool m_valid;
    QDateTime m_dt;
};


#endif // FILEFORMAT_DATAPOINTERTIME_H
