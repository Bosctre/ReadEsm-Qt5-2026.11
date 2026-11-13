#ifndef HTMLREPORTER_H
#define HTMLREPORTER_H

#include "Reporter.h"
#include <QString>
#include <QByteArray>
#include <ostream>
#include <vector>

/// Écrit le rapport au format de la version d'origine de readesm :
/// en-tête + sommaire, une section <h3> par bloc, sous-structures repliables.
class HtmlReporter : public Reporter {
public:
    explicit HtmlReporter(std::ostream& outStream);
    ~HtmlReporter() override = default;

    using Reporter::tagValuePair;
    void tagValuePair(const QString& tag, const QString& value) override;
    void writeBlock(const DataType& block, const QString& title) override;
    void writeArray(const DataType& array, const QString& title, bool expand) override;
    void beginList(const QString& title, int count, bool expand, bool collapsible = true) override;
    void endList() override;

    void setTitle(const QString& title) override { titleStr = title; }
    void startBlock(const QString& title) override;
    void endBlock() override;

    bool allowSvg() const override { return true; }

    void startDocument();
    void endDocument();
    QByteArray toQByteArray() const { return document.toUtf8(); }

private:
    QString openToggle(int id, bool expand) const;
    void countItem();

    int linkNumber  = 0;
    int blockNumber = 0;
    int nestLevel   = 0;

    QString titleStr;
    QString toc;          // sommaire
    QString collected;    // corps du document
    QString document;     // document final
    std::vector<int>  arrayLevel;   // niveau d'imbrication des tableaux en cours d'écriture
    std::vector<int>  arrayCount;   // nombre d'éléments déjà écrits dans chacun
    std::vector<bool> listOpen;     // beginList en cours : <ul> ouvert ?
    std::ostream& outputStream;
};

#endif // HTMLREPORTER_H
