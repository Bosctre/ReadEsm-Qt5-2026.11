#pragma once
#ifndef TEXTSTREAMREPORTER_H
#define TEXTSTREAMREPORTER_H

#include "Reporter/Reporter.h"
#include <QTextStream>


class TextStreamReporter : public Reporter {
public:
    TextStreamReporter(QTextStream &stream);

    void tagValuePair(const QString &tag, const QString &value) override;
    void writeArray(const DataType &array, const QString &title, bool expand) override;

private:
    QTextStream &m_stream;
};


#endif // TEXTSTREAMREPORTER_H

