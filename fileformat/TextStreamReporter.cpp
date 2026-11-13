#include "TextStreamReporter.h"
#include "DataTypes/DataType.h"


TextStreamReporter::TextStreamReporter(QTextStream &stream)
    : m_stream(stream)
{
}

void TextStreamReporter::tagValuePair(const QString &tag, const QString &value)
{
    m_stream << tag << ": " << value << Qt::endl;
}

void TextStreamReporter::writeArray(const DataType &array, const QString &title, bool expand)
{
    Q_UNUSED(expand)
    m_stream << title << ":" << Qt::endl;
    // Ajoutez ici la logique pour écrire les détails de l'array si nécessaire
}


