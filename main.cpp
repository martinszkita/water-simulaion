#include "mainwindow.h"
#include "particle.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QGraphicsScene>
#include <QGraphicsView>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "liquid-simulation_" + QLocale(locale).name();
        if (translator.load(":i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow main_window;



    main_window.show();


    return a.exec();
}
