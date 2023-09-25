#include <QCoreApplication>
#include <QCommandLineParser>
#include "mainwindow.h"

#include <QApplication>

extern QString prgname;
extern QString copyright;
extern QString license;
extern QString version;
QString fileToLoad;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName(prgname);
    QCoreApplication::setApplicationVersion(version);
    QCommandLineParser parser;
    QByteArray h;
    parser.setApplicationDescription(h);
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", QCoreApplication::translate("main", "File to edit."));
    parser.process(a);

    fileToLoad = "";
    const QStringList args = parser.positionalArguments();

    if (args.length()>0) fileToLoad = args.at(0);

    MainWindow w;
    w.show();
    return a.exec();
}
