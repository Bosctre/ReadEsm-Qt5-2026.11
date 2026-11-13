#include "VuDetailedSpeedData.h"
#include "../Reporter/Reporter.h"


VuDetailedSpeedData::VuDetailedSpeedData(const DataPointer& start)
    : RawVuDetailedSpeedData(start)
{}

void VuDetailedSpeedData::printOn(Reporter& report) const {
    RawVuDetailedSpeedData::printOn(report);
}

