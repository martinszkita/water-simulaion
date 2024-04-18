#include "particle.h"
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QGraphicsScene>
#include <QDebug>

Particle::Particle()
{
    pos_x =100;
    pos_y= 100;
}


void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
//    qInfo() << "funkcja paint";
    QPen pen;

    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->setBrush(Qt::red); // wypelnienie
    painter->drawEllipse(pos_x,pos_y,h_x,h_y);
}

QRectF Particle::boundingRect() const
{
    return QRectF();
}

void Particle::move()
{
    pos_x +=10;
    pos_y +=10;

    setPos(pos_x,pos_y);

    scene()->update();
    qInfo() << "przesunalem, teraz pos_x = "<<pos_x<<"a pos_y = "<<pos_y;

}
