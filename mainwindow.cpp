#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "particle.h"

#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // poczatek_x , poczatek_y , w ,h

    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStatusBar(nullptr); // remove bottom bar

    Particle * particle = new Particle(QPointF(5,0));
    scene->addItem(particle);

    // Add the QGraphicsView to the main window
    setCentralWidget(view);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    // Adjust the scene's size whenever the window is resized
    scene->setSceneRect(QRect(QPoint(0, 0), this->size()));
    qInfo() << "resize";
    qInfo() <<"height main window: "<< this->height();
}

