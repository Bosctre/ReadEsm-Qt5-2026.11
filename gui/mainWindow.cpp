#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

#include "mainWindow.h"
#include "../fileformat/EsmFile.h"
#include "../fileformat/Reporter/HtmlReporter.h"
#include <sstream>
#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
    view = new SvgTextBrowser(this);
    view = new SvgTextBrowser(this); 
    view->setOpenExternalLinks(true);
    setCentralWidget(view);

    QMenu* fileMenu = new QMenu(tr("&File"), this);
    QAction* fileOpenAction = new QAction(tr("&Open..."), this);
    QAction* fileSaveRawAction = new QAction(tr("&Save as..."), this);
    QAction* fileSaveHtmlAction = new QAction(tr("Export as HTML..."), this);
    QAction* fileQuitAction = new QAction(tr("&Quit"), this);

    fileOpenAction->setShortcut(QKeySequence::Open);
    fileSaveRawAction->setShortcut(QKeySequence::SaveAs);
    fileQuitAction->setShortcut(QKeySequence::Quit);

    connect(fileQuitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(fileSaveRawAction, SIGNAL(triggered()), this, SLOT(saveRaw()));
    connect(fileSaveHtmlAction, SIGNAL(triggered()), this, SLOT(saveHtml()));

    fileMenu->addAction(fileOpenAction);
    fileMenu->addSeparator();
    fileMenu->addAction(fileSaveRawAction);
    fileMenu->addAction(fileSaveHtmlAction);
    fileMenu->addSeparator();
    fileMenu->addAction(fileQuitAction);
    menuBar()->addMenu(fileMenu);

    QMenu* helpMenu = new QMenu(tr("&Help"), this);
    QAction* helpAboutAction = new QAction(tr("&About Readesm"), this);
    QAction* helpAboutQtAction = new QAction(tr("About &Qt"), this);

    connect(helpAboutAction, SIGNAL(triggered()), this, SLOT(helpAbout()));
    connect(helpAboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    helpMenu->addAction(helpAboutQtAction);
    helpMenu->addAction(helpAboutAction);
    menuBar()->addMenu(helpMenu);

    resize(940, 700);
}

void mainWindow::helpAbout()
{
    QMessageBox::about(this, tr("About Readesm"),
        tr("readesm - Digital tachograph file reader\n\nFree software under GPL v3."));
}

void mainWindow::helpContents() {}
void mainWindow::print() {}
void mainWindow::onOpenDDD() { openFile(); }

void mainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Tachograph File"), QString(),
        tr("Tachograph Files") + " (*.esm *.ddd *.tgd *.add);;" + tr("All files") + " (*)");
    if (!fileName.isEmpty()) openFile(fileName);
}

void mainWindow::openFile(const QString& filename)
{
    esm.reset(new EsmFile(filename));

    std::ostringstream oss;
    HtmlReporter rep(oss);
    rep.startDocument();
    esm->printOn(rep);
    rep.endDocument();

    // Selon l'implémentation de HtmlReporter, le HTML est écrit dans le flux
    // ou conservé en interne : on prend ce qui n'est pas vide.
    const std::string out = oss.str();
    htmlContent = out.empty() ? rep.toQByteArray()
                              : QByteArray(out.data(), int(out.size()));

    if (!esm->errorLog().isEmpty())
        QMessageBox::warning(this, tr("Error"), esm->errorLog());

    view->setHtmlWithSvg(QString::fromUtf8(htmlContent));
}

void mainWindow::saveHtml()
{
    if (htmlContent.isEmpty()) {
        QMessageBox::warning(this, tr("Saving not possible"), tr("Nothing opened."));
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save HTML file as"), esm->suggestFileName() + ".html",
        tr("HTML files") + " (*.html);;" + tr("All files") + " (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) file.write(htmlContent);
    }
}

void mainWindow::saveRaw()
{
    if (!esm) {
        QMessageBox::warning(this, tr("Saving not possible"), tr("Nothing opened."));
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Tachograph file as"), esm->suggestFileName() + ".esm",
        tr("Tachograph Files") + " (*.esm *.ddd *.tgd *.add);;" + tr("All files") + " (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) file.write(esm->fileData);
    }
}
#endif // MAINWINDOW_CPP