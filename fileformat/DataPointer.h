#pragma once
#ifndef DATAPOINTER_H
#define DATAPOINTER_H

#include <QByteArray>


class DataPointer {
public:
    DataPointer(const QByteArray* dataPtr = nullptr, int offset = 0, int length = 0);

    bool isValid() const;
    quint8 readU8() const;
    quint16 readU16() const;
    quint32 readU24() const;
    quint32 readU32() const;
    quint8 operator[](int i) const;
    DataPointer operator+(int delta) const;
    DataPointer& operator+=(int delta); // Ajout de la déclaration de l'opérateur +=
    DataPointer slice(int offset, int length) const;
    int offset() const;
    int bytesLeft() const;
     const char* getData() const;

private:
    const QByteArray* m_data;
    int m_offset;
    int m_length;
};


#endif // DATAPOINTER_H
