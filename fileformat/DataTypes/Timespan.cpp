#include "Timespan.h"
#include <QDateTime>
#include <QLocale>

Timespan::Timespan(DataPointer start)
    : DataType(start), begin(start), end(start + 4) {}

static QString hms(qint64 s) {
    return QString("%1:%2:%3").arg(s / 3600)
        .arg((s / 60) % 60, 2, 10, QChar('0'))
        .arg(s % 60, 2, 10, QChar('0'));
}

QString Timespan::toString() const {
    const quint32 b = begin.seconds(), e = end.seconds();
    if (b == 0 && e == 0) return QStringLiteral("undefined");
    if (b == e) return begin.toString();

    const QLocale loc;
    const QDateTime db = begin.toDateTime(), de = end.toDateTime();
    const QString dur = hms(qint64(e) - qint64(b));

    if (db.date() == de.date())
        return QString("On %1, from %2 to %3 (%4)")
            .arg(loc.toString(db.date(), "ddd MMM d yyyy"),
                 loc.toString(db.time(), "HH:mm:ss"),
                 loc.toString(de.time(), "HH:mm:ss"), dur);

    return QString("From %1 to %2 (%3)").arg(begin.toString(), end.toString(), dur);
}

void Timespan::printOn(Reporter& report) const {
    report.tagValuePair(QObject::tr("begin"), begin.toString());
    report.tagValuePair(QObject::tr("end"), end.toString());
}