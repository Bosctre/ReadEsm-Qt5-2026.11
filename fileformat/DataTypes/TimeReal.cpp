#include "TimeReal.h"
#include "../Reporter/Reporter.h"
#include "../readTypes.h"
#include <QLocale>
#include <QObject>
#include <QTime>

TimeReal::TimeReal(const DataPointer& filewalker)
    : DataType(filewalker), secs(quint32(readBigEndianInt4(filewalker))) {}

QString TimeReal::className() const { return "TimeReal"; }

int TimeReal::size() const { return 4; }

QDateTime TimeReal::toDateTime() const {
    return QDateTime::fromSecsSinceEpoch(qint64(secs), Qt::UTC);
}

QString TimeReal::toString() const {
    if (secs == 0) return QStringLiteral("undefined");
    const QDateTime dt = toDateTime();
    if (dt.time() == QTime(0, 0, 0))
        return QLocale().toString(dt.date(), "ddd MMM d yyyy");     // sam. mai 24 2025
    return QLocale().toString(dt, "ddd d. MMM HH:mm:ss yyyy");      // lun. 13. sept. 23:59:59 2027
}

QString TimeReal::dateString() const {
    return QLocale().toString(toDateTime().date(), "ddd MMM d yyyy");
}

void TimeReal::printOn(Reporter& report) const {
    report.tagValuePair(QObject::tr("TimeReal"), toString());
}