#include "KeyIdentifier.h"
#include "../Reporter/Reporter.h"
#include <QObject>


KeyIdentifier::KeyIdentifier(const DataPointer& start)
    : DataType(start)
{
}

QString KeyIdentifier::className() const
{
    return "KeyIdentifier";
}

int KeyIdentifier::size() const
{
    return 4; // Remplacez par la taille réelle
}

void KeyIdentifier::printOn(Reporter& report) const
{
    report.tagValuePair(QObject::tr("Key Identifier"), QString());
}


