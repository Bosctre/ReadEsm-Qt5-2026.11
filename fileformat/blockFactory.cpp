#include "blockFactory.h"
#include "CardBlocks/cardBlockFactory.h"
#include "VuBlocks/vuBlockFactory.h"
#include <QtCore/QDebug>


QSharedPointer<TopLevelBlock> blockFactory(const DataPointer& start) {
    QSharedPointer<TopLevelBlock> rv;
    if (start[0] == 0x76) rv = vuBlockFactory(start);
    else rv = qSharedPointerCast<TopLevelBlock>(cardBlockFactory(start));
    return rv;
}

