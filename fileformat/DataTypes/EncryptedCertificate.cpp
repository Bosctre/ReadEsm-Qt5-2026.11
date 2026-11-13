#include "EncryptedCertificate.h"
#include "../Reporter/Reporter.h"
#include <QObject>


EncryptedCertificate::EncryptedCertificate(const DataPointer& filewalker)
    : DataType(filewalker)
{
    // Initialisation
}

QString EncryptedCertificate::className() const
{
    return "EncryptedCertificate";
}

int EncryptedCertificate::size() const
{
    return 0; // Remplacez par la taille réelle
}

void EncryptedCertificate::printOn(Reporter& report) const
{
    report.tagValuePair(QObject::tr("Encrypted Certificate"), QString());
}

