#ifndef LASTCARDDOWNLOAD_H
#define LASTCARDDOWNLOAD_H

#include "../DataTypes/TimeReal.h"
#include "CardBlock.h"

class LastCardDownload : public CardBlock {
	Q_DECLARE_TR_FUNCTIONS(LastCardDownload)
public:
	
	TimeReal lastCardDownload;

	LastCardDownload(const DataPointer& filewalker);
	///returns "LastCardDownload"
QString className() const;
	QString title() const;
	static const int Type = 0x050e;
	virtual void printOn(Reporter& report) const;
};


#endif
