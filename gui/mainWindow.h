#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include "SvgTextBrowser.h"
#include <QSharedPointer>
#include <QByteArray>
#include <QString>

class EsmFile;

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = nullptr);

public slots:
    void openFile();
    void openFile(const QString& filename);
    void helpContents();
    void print();
    void saveRaw();
    void saveHtml();
    void helpAbout();

private slots:
    void onOpenDDD();

private:
    void displayReport(const QString& text);
    QSharedPointer<EsmFile> esm;
    QByteArray htmlContent;
    SvgTextBrowser* view;
};

#endif // MAINWINDOW_H