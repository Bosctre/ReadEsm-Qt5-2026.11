#include "CardBlock.h"
#include "../readTypes.h"
#include "../DataTypes/RawData.h"
#include "../Reporter/Reporter.h"
#include <QCoreApplication>

CardBlock::CardBlock(const DataPointer& filewalker) : TopLevelBlock(filewalker) {}

QString CardBlock::className() const {
    return "CardBlock";
}

int CardBlock::tag() const {
    return readBigEndianInt2(start);
}

int CardBlock::size() const {
    return 5 + readBigEndianInt2(start + 3);
}

DataPointer CardBlock::payload() const {
    return start + 5;
}

int CardBlock::dataBlockSize() const {
    return size();
}

QString CardBlock::title() const {
    return QCoreApplication::translate("CardBlock", "Unknown block with tag 0x%1")
            .arg(tag(), 4, 16, QChar('0'));
}

void CardBlock::printOn(Reporter& report) const {
    // Affichage minimal pour les blocs inconnus ; les blocs générés redéfinissent printOn
    report.tagValuePair(QCoreApplication::translate("CardBlock", "Payload size"), size() - 5);
    report.writeBlock(RawData(start + 5, size() - 5), QCoreApplication::translate("CardBlock", "data"));
}