#include "particle.h"
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <QBrush>
Particle::Particle(QWidget * parent) : QWidget(parent)
{
    //this->update(); // wymuszanie odswiezenia zeby wywolac paintEvent()
}

void Particle::paintEvent(QPaintEvent *pEvent)
{
    QPainter painter(this);
    QPen pen;

    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.setBrush(Qt::red); // wypelnienie
    painter.drawEllipse(100,100,50,50);
}
