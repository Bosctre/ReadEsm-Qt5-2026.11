#ifndef CARDHEADER_H
#define CARDHEADER_H

#include "../DataTypes/DataType.h"
#include "../DataPointer.h"
#include <QByteArray>


class CardHeader : public DataType {
public:
    CardHeader(const DataPointer& start);

    QString className() const override;
    int size() const override;
    QString title() const;
    void printOn(Reporter& report) const override;

private:
    DataPointer m_start;
    QByteArray headerBytes;
};


#endif // CARDHEADER_H