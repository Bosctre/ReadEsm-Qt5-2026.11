#ifndef READTYPES_H
#define READTYPES_H

#include <QString>

/// Octet BCD -> deux chiffres décimaux (0x25 -> "25")
QString bcdbyte(unsigned char b);
    
class DataPointer;   // <- AJOUT OBLIGATOIRE

QString codepageStringCombination(const DataPointer& start, int length);
QString fixedString(const DataPointer& start, int length);

int readBigEndianInt1(const DataPointer& start);
int readBigEndianInt2(const DataPointer& start);
int readBigEndianInt3(const DataPointer& start);
int readBigEndianInt4(const DataPointer& start);

QString bcdbyte(unsigned char start);
QString hexByte(unsigned char start);


#endif