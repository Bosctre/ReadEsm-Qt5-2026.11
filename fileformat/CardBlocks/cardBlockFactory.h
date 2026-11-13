#ifndef CARDBLOCKFACTORY_H
#define CARDBLOCKFACTORY_H

#include <QtCore/QSharedPointer>
#include "CardBlock.h"

QSharedPointer<CardBlock> cardBlockFactory(const DataPointer& start);
#endif
