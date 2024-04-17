#include "mainwindow.h"
#include "ball.h"
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
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QGraphicsScene scene;
    scene.setSceneRect(-200,-200,400,400);

    Particle * particle = new Particle();
    scene.addItem(particle);

    QGraphicsView view(&scene);
    view.show();

    return a.exec();
}
