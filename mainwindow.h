#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "liquidsimulation.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class
 * Represents the window for the scene.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent * event) override;
    void on_resizeEvent(QResizeEvent * event);
private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QGraphicsView * view;
    LiquidSimulation * simulation;
};
#endif // MAINWINDOW_H
