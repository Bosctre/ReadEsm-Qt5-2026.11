#include "CardAccessRights.h"
#include "../Reporter/Reporter.h"  // Assurez-vous que cette ligne est présente


CardAccessRights::CardAccessRights(const DataPointer& start) : DataType(start), m_start(start) {}

QString CardAccessRights::className() const {
    return "CardAccessRights";
}

int CardAccessRights::size() const {
    return 1; // Remplacez par la taille réelle de vos données
}

void CardAccessRights::printOn(Reporter& report) const {
    // Implémentez l'affichage des informations spécifiques à CardAccessRights
}

