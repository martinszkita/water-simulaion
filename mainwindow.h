#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
};
#endif // MAINWINDOW_H
