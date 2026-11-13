#include "RawCardDriverActivity.h"

RawCardDriverActivity::RawCardDriverActivity(const DataPointer& filewalker) : CardBlock(filewalker),
	oldestRecord(readBigEndianInt2(start + 5 )),
	newestRecord(readBigEndianInt2(start + 7 )),
	cyclicData(start + 9 , dataBlockSize() - (9 ))
{}

QString RawCardDriverActivity::className() const {
	return "RawCardDriverActivity";
}

QString RawCardDriverActivity::title() const {
	return tr("Driver Activity Data");
}

void RawCardDriverActivity::printOn(Reporter& report) const {
	report.tagValuePair(tr("oldestRecord"), oldestRecord);
	report.tagValuePair(tr("newestRecord"), newestRecord);
	report.tagValuePair(tr("cyclicData"), cyclicData.toString());if(size() != 9 ){ report.tagValuePair("should have", 9 ); report.tagValuePair("has", size()); }
}

