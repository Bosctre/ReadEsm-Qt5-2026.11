#include "VuOverview.h"


VuOverview::VuOverview(const DataPointer& filewalker) : RawVuOverview(filewalker)
{}

///In the overview block, the bytes in the two certificates do not count for the checksum calculation
RawData VuOverview::signedBytes() const {
    // Après l'en-tête (2 octets) et les deux certificats (2 x 194 octets) :
    // les données signées vont jusqu'à la fin du bloc de données
    const int skipped = 2 + 194 * 2;
    return RawData(start + skipped, dataBlockSize() - (194 * 2));
}

