#include "DataType.h"
#include "../Reporter/Reporter.h"

DataType::DataType(const DataPointer& s) : start(s) {}

QString DataType::toString() const {
    return QString();       // vide : pas de lien show/hide, contenu affiché directement
}

