#include "ActivityChangeInfo.h"
#include "../readTypes.h"
#include "../Reporter/Reporter.h"

ActivityChangeInfo::ActivityChangeInfo(const DataPointer& start) : DataType(start) {
    const quint16 w = readBigEndianInt2(start);
    slot          = (w >> 15) & 1;
    drivingStatus = (w >> 14) & 1;
    cardStatus    = (w >> 13) & 1;
    activity      = (w >> 11) & 3;
    minutes       =  w        & 0x7FF;
}

void ActivityChangeInfo::printOn(Reporter& report) const {
    report.tagValuePair(QObject::tr("Slot"),     int(slot));
    report.tagValuePair(QObject::tr("Activity"), int(activity));
    report.tagValuePair(QObject::tr("Minutes"),  int(minutes));
}