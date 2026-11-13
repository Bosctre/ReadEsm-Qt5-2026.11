#include "Reporter.h"
#include "../DataTypes/DataType.h"

bool Reporter::allowSvg() const { return false; }

// Repli : le bloc est traité comme un tableau déplié
void Reporter::writeBlock(const DataType& block, const QString& title) {
    writeArray(block, title, true);
}

// Repli pour les reporters texte
void Reporter::beginList(const QString& title, int count, bool /*expand*/, bool /*collapsible*/) {
    tagValuePair(title, count);
}
void Reporter::endList() {}
