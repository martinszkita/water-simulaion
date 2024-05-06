#include "mainwindow.h"
#include "particle.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScreen>
#include<random>
#include<ctime>


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
    scene.setSceneRect(0,0,800,600);

    QGraphicsView view(&scene);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view.fitInView();

    QVector<Particle> kuleczki;
    srand(time(NULL));
    for (int i = 0 ; i < 1 ; i++){
        Particle * particle = new Particle(QPointF(20,0));
        scene.addItem(particle);
    }

    //Particle * particle = new Particle(QPointF(5,0));
   // scene.addItem(particle);


    view.show();

    return a.exec();
}
