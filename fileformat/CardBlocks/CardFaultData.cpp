#include "CardFaultData.h"

CardFaultData::CardFaultData(const DataPointer& filewalker) : CardBlock(filewalker),
	cardFaultRecords(Subblocks<CardEventRecord>::fromTypeAndLength(start + 5 , dataBlockSize() - (5 )))
{}

QString CardFaultData::className() const {
	return "CardFaultData";
}

QString CardFaultData::title() const {
	return tr("Faults Data");
}

void CardFaultData::printOn(Reporter& report) const {
	report.writeArray(cardFaultRecords, tr("cardFaultRecords"));if(size() != 5  + cardFaultRecords.size()){ report.tagValuePair("should have", 5  + cardFaultRecords.size()); report.tagValuePair("has", size()); }
}

