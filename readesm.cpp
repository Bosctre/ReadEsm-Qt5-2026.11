#ifndef READESM_CPP
#define READESM_CPP

#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QLocale>
#include <QScopedPointer>
#include <QTextStream>
#include <QTranslator>
#include <QGuiApplication>
#include <QIcon>
#include <cstdio>
#include <sstream>
#include "fileformat/config.h"
#include "fileformat/EsmFile.h"
#include "fileformat/Reporter/HtmlReporter.h"
#include "gui/mainWindow.h"
#include "OptionParser.h"

#ifdef Q_OS_WIN
// Windows: graphical program without console window. When started from a console
// (command-line use), attach to it so that its messages remain visible.
#ifndef NOMINMAX
#define NOMINMAX
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
namespace {
struct ParentConsoleAttach {
    ParentConsoleAttach() {
        if (!AttachConsole(ATTACH_PARENT_PROCESS)) return;
        if (GetFileType(GetStdHandle(STD_OUTPUT_HANDLE)) == FILE_TYPE_UNKNOWN) freopen("CONOUT$", "w", stdout);
        if (GetFileType(GetStdHandle(STD_ERROR_HANDLE)) == FILE_TYPE_UNKNOWN) freopen("CONOUT$", "w", stderr);
    }
};
const ParentConsoleAttach parentConsoleAttach;
}
#endif

int main(int argc, char** argv)
{
    QTextStream cerr(stderr);
    QTextStream cout(stdout);

    OptionParser parser;
    parser.addOption("format", "f", "Format used for output");
    parser.addOption("locale", "l", "Language used for output");
    parser.parseArgs(argc, argv);

    if (parser.checkFlag("help")) {
        cout << "Readesm " << QString("%1 (%2)").arg(VERSION).arg(VERSION_DATE);
        cout << "\n\n Ce programme permet l'interprétation des données issues d'un Chronotachygraphe avec des programmes comme Cardpeek dans un format humainement compréhensible\n\n";
        cout << "usage: Readesm [OPTIONS] [INPUT FILE [OUTPUT FILE]]\n\n";
        cout << parser.helpText();
        cout << "\n\n Being a QT (http://qt.nokia.com/) application, you can also pass qt command line parameters to Readesm.";
        cout << "\n\n  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\n This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n";
        return 0;
    }

    // Moins de 2 arguments : interface graphique ; sinon : conversion en console.
    const bool gui = (parser.argumentCount() < 2);

    QScopedPointer<QCoreApplication> app(gui ? new QApplication(argc, argv)
                                             : new QCoreApplication(argc, argv));
    app->setApplicationName("Readesm");
        if (gui) {
        #ifdef Q_OS_WIN
        QIcon ic(":/readesm.svg");
#else
        QIcon ic = QIcon::fromTheme("readesm", QIcon(QString(PREFIX) + "/share/icons/hicolor/scalable/apps/readesm.svg"));
#endif
        QGuiApplication::setWindowIcon(ic);
        QGuiApplication::setDesktopFileName("readesm");     // lien avec readesm.desktop sous Wayland/GNOME
    }
    app->setApplicationVersion(QString("%1 (%2)").arg(VERSION).arg(VERSION_DATE));
    app->setOrganizationName(QString::fromUtf8("Andreas Gölzer"));
    app->setOrganizationDomain("http://andreas.goelzer.de");

    // Traduction : sans fichier .qm, on reste en anglais. Le message n'est affiché
    // que si l'utilisateur a demandé explicitement une langue avec --locale.
    QTranslator qTranslator;
    const QString requestedLocale = parser.get("locale", QString());
    const QString locale = requestedLocale.isEmpty() ? QLocale::system().name() : requestedLocale;
    if (locale != "C") QLocale::setDefault(QLocale(locale));
    if (locale != "C") {
        const QString trans = "readesm_" + locale;
        const bool loaded = qTranslator.load(trans)
            || qTranslator.load(trans, QCoreApplication::applicationDirPath() + "/../translations")
            || qTranslator.load(trans, PREFIX "/share/readesm/translations");
        if (loaded)
            app->installTranslator(&qTranslator);
        else if (!requestedLocale.isEmpty())
            cerr << "Could not load internationalization files for locale " << locale << Qt::endl;
    }

    if (!gui) {
        if (parser.argumentCount() > 2) {
            cerr << "too many arguments to readesm" << Qt::endl;
            return 1;
        }
        const QString inputFile(parser.getArgument(0));
        const QString outputFile(parser.getArgument(1));
        const QString extension(outputFile.section(".", -1).toLower());

        QByteArray outData;
        bool converted = false;
        if (parser.get("format") == "html" || extension == "html" || extension == "htm" || extension == "xhtml") {
            EsmFile esm(inputFile);
            std::ostringstream oss;
            HtmlReporter rep(oss);
            rep.startDocument();
            esm.printOn(rep);
            rep.endDocument();

            // Selon HtmlReporter, le HTML est dans le flux ou conservé en interne
            const std::string out = oss.str();
            outData = out.empty() ? rep.toQByteArray()
                                  : QByteArray(out.data(), int(out.size()));
            converted = true;
        }
        if (!converted) {
            cerr << "Format for output not recognized." << Qt::endl;
            return 1;
        }

        if (outputFile != "-") {
            QFile out(outputFile);
            if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                cerr << "Could not open file " << outputFile << " for output. dumping to stdout" << Qt::endl;
                cerr.flush();
                fwrite(outData.constData(), 1, size_t(outData.size()), stdout);
                return 1;
            }
            out.write(outData);
        } else {
            fwrite(outData.constData(), 1, size_t(outData.size()), stdout);
        }
        return 0;
    }

    mainWindow widgetMainWindow;
    widgetMainWindow.show();
    if (parser.argumentCount() == 1)
        widgetMainWindow.openFile(parser.getArgument(0));
    return app->exec();
}

#endif // READESM_CPP
