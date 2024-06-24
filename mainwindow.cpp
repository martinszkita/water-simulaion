#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "particle.h"
#include <QScreen>
#include <QVector>
#include <QPointF>
#include <random>
#include "liquidsimulation.h"

qreal screen_width = 800; ///< sets up the width of the screen
qreal screen_height = 600; ///< sets up the height of the screen


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,screen_height,screen_width); // poczatek_x , poczatek_y , w ,h

    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStatusBar(nullptr); // remove bottom bar

    simulation = new LiquidSimulation();

    ///< add all the simulation particles to the scene
    for(auto & particle : simulation->particles){
        scene->addItem(particle);
    }

    setCentralWidget(view);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    scene->setSceneRect(QRect(QPoint(0, 0), this->size()));
    //qInfo() << "resize";
}

