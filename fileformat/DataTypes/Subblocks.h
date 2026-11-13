#pragma once
#ifndef FILEFORMAT_SUBBLOCKS_H
#define FILEFORMAT_SUBBLOCKS_H

#include "DataType.h"
#include "../DataPointer.h"
#include "../Reporter/Reporter.h"
#include <vector>


template<typename T>
class Subblocks : public DataType {
public:
    Subblocks() : DataType(DataPointer()), numberOfBytes(0) {}
    Subblocks(const DataPointer& start);

    QString className() const override;
    int size() const override;
    void printOn(Reporter& o) const override;

    static Subblocks fromTypeAndCount(const DataPointer& start, int count);
    static Subblocks fromTypeAndLength(const DataPointer& start, int length);

    const std::vector<T>& getSubblocks() const { return subblocks; }

private:
    std::vector<T> subblocks;
    int numberOfBytes;
};

template<typename T>
Subblocks<T>::Subblocks(const DataPointer& start)
    : DataType(start), numberOfBytes(0)
{}

template<typename T>
QString Subblocks<T>::className() const {
    return "Subblocks";
}

template<typename T>
int Subblocks<T>::size() const {
    return numberOfBytes;               // inclut les éléments vides qui ne sont pas conservés
}

template<typename T>
void Subblocks<T>::printOn(Reporter& o) const {
    // Chaque élément passe par writeBlock : <li>, repli "show" et comptage par le reporter
    for (const auto& item : subblocks)
        o.writeBlock(item, QString());
}

template<typename T>
Subblocks<T> Subblocks<T>::fromTypeAndCount(const DataPointer& start, int count) {
    Subblocks<T> result;
    DataPointer walker = start;
    for (int i = 0; i < count; ++i) {
        if (walker.bytesLeft() <= 0) break;            // fichier tronqué
        T item(walker);
        const int itemSize = item.size();
        if (itemSize <= 0) break;                      // garde-fou
        if (!item.isEmpty()) result.subblocks.push_back(item);
        result.numberOfBytes += itemSize;
        walker += itemSize;
    }
    return result;
}

template<typename T>
Subblocks<T> Subblocks<T>::fromTypeAndLength(const DataPointer& start, int length) {
    Subblocks<T> result;
    DataPointer walker = start;
    int consumed = 0;
    while (consumed < length && walker.bytesLeft() > 0) {
        T item(walker);
        const int itemSize = item.size();
        if (itemSize <= 0) break;                      // garde-fou contre boucle infinie
        if (!item.isEmpty()) result.subblocks.push_back(item);
        result.numberOfBytes += itemSize;
        walker += itemSize;
        consumed += itemSize;
    }
    return result;
}

#endif // FILEFORMAT_SUBBLOCKS_H