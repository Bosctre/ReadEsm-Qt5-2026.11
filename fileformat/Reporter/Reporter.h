#ifndef REPORTER_H
#define REPORTER_H

#include <QString>

class DataType;

class Reporter {
public:
    virtual ~Reporter() = default;

    /// Paire nom/valeur (seule surcharge à implémenter dans les sous-classes)
    virtual void tagValuePair(const QString& tag, const QString& value) = 0;

    /// Surcharges de confort
    void tagValuePair(const QString& tag, const char* value)  { tagValuePair(tag, QString::fromUtf8(value)); }
    void tagValuePair(const QString& tag, int value)          { tagValuePair(tag, QString::number(value)); }
    void tagValuePair(const QString& tag, unsigned int value) { tagValuePair(tag, QString::number(value)); }
    void tagValuePair(const QString& tag, qlonglong value)    { tagValuePair(tag, QString::number(value)); }
    void tagValuePair(const QString& tag, double value)       { tagValuePair(tag, QString::number(value)); }

    /// Sous-structure (nom + contenu replié si le type a un toString())
    virtual void writeBlock(const DataType& block, const QString& title);

    /// Tableau de sous-structures ; le nombre d'éléments est compté par le reporter
    virtual void writeArray(const DataType& array, const QString& title, bool expand = true) = 0;

    /// Liste écrite à la main (ex. CardDriverActivity) : beginList(...), N x writeBlock(...), endList()
    virtual void beginList(const QString& title, int count, bool expand, bool collapsible = true);
    virtual void endList();

    /// Structure du document : titre, puis une section par bloc de premier niveau
    virtual void setTitle(const QString& /*title*/) {}
    virtual void startBlock(const QString& /*title*/) {}
    virtual void endBlock() {}

    virtual bool allowSvg() const;
    virtual void svgGraph(const QString& /*svgContent*/) {}
};

#endif // REPORTER_H
