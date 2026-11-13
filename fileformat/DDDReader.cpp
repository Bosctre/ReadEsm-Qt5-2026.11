#include "DDDReader.h"
#include "DataPointer.h"
#include "Reporter/Reporter.h"
#include "CardBlocks/Identification.h"
#include "TextStreamReporter.h"
#include <QFile>
#include <QTextStream>


bool readDDD(const QString &filePath, QString &error, QString &output)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        error = QObject::tr("Failed to open file: %1").arg(filePath);
        return false;
    }

    QByteArray data = file.readAll();
    DataPointer p(&data, 0, data.size());

    QString buffer;
    QTextStream out(&buffer, QIODevice::WriteOnly);
    TextStreamReporter rep(out); // Utilisation de TextStreamReporter

    // Utilisation de Identification
    Identification id(p);
    id.printOn(rep);

    output = buffer;
    return true;
}


