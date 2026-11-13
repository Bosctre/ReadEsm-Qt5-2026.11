#include "DataPointer.h"
#include <QtEndian>


// Constructeur
DataPointer::DataPointer(const QByteArray* dataPtr, int offset, int length)
    : m_data(dataPtr), m_offset(offset), m_length(0) {
    if (dataPtr && offset >= 0 && offset < dataPtr->size()) {
        int maxLen = dataPtr->size() - offset;
        m_length = (length <= 0 || length > maxLen) ? maxLen : length;
    }
}

// Vérifie si le pointeur est valide
bool DataPointer::isValid() const {
    return m_data != nullptr && m_offset >= 0 && m_length >= 0 && (m_offset + m_length) <= m_data->size();
}

// Lecture d'un octet
quint8 DataPointer::readU8() const {
    if (!isValid() || m_length < 1) return 0;
    return static_cast<quint8>(m_data->at(m_offset));
}

// Lecture d'un uint16 (big-endian)
quint16 DataPointer::readU16() const {
    if (!isValid() || m_length < 2) return 0;
    const uchar* p = reinterpret_cast<const uchar*>(m_data->constData() + m_offset);
    return qFromBigEndian<quint16>(p);
}

// Lecture d'un uint24 (big-endian)
quint32 DataPointer::readU24() const {
    if (!isValid() || m_length < 3) return 0;
    const uchar* p = reinterpret_cast<const uchar*>(m_data->constData() + m_offset);
    return (static_cast<quint32>(p[0]) << 16) |
           (static_cast<quint32>(p[1]) << 8)  |
           static_cast<quint32>(p[2]);
}

// Lecture d'un uint32 (big-endian)
quint32 DataPointer::readU32() const {
    if (!isValid() || m_length < 4) return 0;
    const uchar* p = reinterpret_cast<const uchar*>(m_data->constData() + m_offset);
    return qFromBigEndian<quint32>(p);
}

// Accès par index
quint8 DataPointer::operator[](int i) const {
    if (!isValid() || i < 0 || i >= m_length) return 0;
    return static_cast<quint8>(m_data->at(m_offset + i));
}

// Opérateur +
DataPointer DataPointer::operator+(int delta) const {
    if (!isValid() || delta < 0 || delta > m_length) {
        return DataPointer(nullptr, 0, 0);
    }
    return DataPointer(m_data, m_offset + delta, m_length - delta);
}

// Opérateur +=
DataPointer& DataPointer::operator+=(int delta) {
    if (isValid() && delta >= 0 && (m_offset + delta) <= m_data->size()) {
        m_offset += delta;
        m_length -= delta;
        if (m_length < 0) {
            m_length = 0;
        }
    } else {
        m_offset = 0;
        m_length = 0;
    }
    return *this;
}

// Slice
DataPointer DataPointer::slice(int offset, int length) const {
    if (!isValid() || offset < 0) {
        return DataPointer(nullptr, 0, 0);
    }
    int newOffset = m_offset + offset;
    if (newOffset >= m_data->size()) {
        return DataPointer(nullptr, 0, 0);
    }
    int newLen = length <= 0 ? m_length - offset : length;
    if (newLen <= 0 || newOffset + newLen > m_data->size()) {
        newLen = m_data->size() - newOffset;
        if (newLen < 0) {
            newLen = 0;
        }
    }
    return DataPointer(m_data, newOffset, newLen);
}

// Accesseurs
int DataPointer::offset() const {
    return m_offset;
}

int DataPointer::bytesLeft() const {
    return isValid() ? m_length : 0;
}

// Méthode pour accéder aux données sous-jacentes
const char* DataPointer::getData() const {
    if (!isValid()) {
        return nullptr;
    }
    return m_data->constData() + m_offset;
}

