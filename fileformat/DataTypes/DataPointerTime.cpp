#include "DataPointerTime.h"
#include <QDateTime>


static const QDateTime EPOCH_TACHO = QDateTime(QDate(1992, 1, 1), QTime(0, 0), Qt::UTC);

DataPointerTime::DataPointerTime()
    : m_valid(false), m_dt()
{
}

DataPointerTime::DataPointerTime(const DataPointer& ptr)
    : m_valid(false), m_dt()
{
    // Vérifiez si le DataPointer est valide et a suffisamment de données
    if (!ptr.isValid() || ptr.bytesLeft() < 4) {
        m_valid = false;
        return;
    }

    // Utilisez getData() pour obtenir un pointeur vers les données
    const unsigned char* p = reinterpret_cast<const unsigned char*>(ptr.getData());

    quint32 minutesBE = (static_cast<quint32>(p[0]) << 24) |
                        (static_cast<quint32>(p[1]) << 16) |
                        (static_cast<quint32>(p[2]) << 8)  |
                        (static_cast<quint32>(p[3]));

    // Convention : 0xFFFFFFFF = undefined
    if (minutesBE == 0xFFFFFFFFu) {
        m_valid = false;
        return;
    }

    // Convert minutes to seconds
    m_dt = EPOCH_TACHO.addSecs(static_cast<qint64>(minutesBE) * 60LL);
    m_valid = true;
}

bool DataPointerTime::isValid() const
{
    return m_valid;
}

QDate DataPointerTime::date() const
{
    return m_valid ? m_dt.date() : QDate();
}

QTime DataPointerTime::time() const
{
    return m_valid ? m_dt.time() : QTime();
}

QString DataPointerTime::toString() const
{
    return m_valid ? m_dt.toString(Qt::ISODate) : QStringLiteral("undefined");
}

int DataPointerTime::secsTo(const DataPointerTime& other) const
{
    if (!m_valid || !other.m_valid) return 0;
    return m_dt.secsTo(other.m_dt);
}

bool DataPointerTime::operator==(const DataPointerTime& other) const
{
    if (!m_valid || !other.m_valid) return false;
    return m_dt == other.m_dt;
}

