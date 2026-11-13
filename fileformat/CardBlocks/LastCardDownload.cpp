#include "LastCardDownload.h"

LastCardDownload::LastCardDownload(const DataPointer& filewalker) : CardBlock(filewalker),
	lastCardDownload(start + 5 )
{}

QString LastCardDownload::className() const {
	return "LastCardDownload";
}

QString LastCardDownload::title() const {
	return tr("Card Download");
}

void LastCardDownload::printOn(Reporter& report) const {
	report.tagValuePair(tr("lastCardDownload"), lastCardDownload.toString());if(size() != 9 ){ report.tagValuePair("should have", 9 ); report.tagValuePair("has", size()); }
}

