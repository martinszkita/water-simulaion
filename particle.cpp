#include "particle.h"
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <random>
#include <QPointF>

float gravity = 0.2;
float collision_factor = 1;

Particle::Particle(const Particle &other): QGraphicsItem(), QObject()
{

    this->position= other.position;
    this->velocity = other.velocity;
    this->r= other.r;

}

Particle::Particle(QPointF pos): position(pos)
{
    QTimer * timer = new QTimer();
    this->kolor = QColor(rand()%255,rand()%255,rand()%255);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(16);

}
void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen;
    pen.setWidth(2);
    pen.setColor(this->kolor);
    painter->setPen(pen);
    painter->setBrush(this->kolor); // wypelnienie
    painter->drawEllipse(position,2*r,2*r);

}

QRectF Particle::boundingRect() const
{
    return QRectF();
}

void Particle::resolve_collisions(){

    // uderzenie w lewa sciane
    if (position.rx() < 0){
        velocity.rx() *= -1 * collision_factor;
        position.rx() = 0;
    }
    // prawa sciana
    else if(position.rx() + 2*r > scene()->width()){
        velocity.rx() *= -1*collision_factor;
        position.rx() = scene()->width() - 2*r;
    }
    // gora
    if(position.ry() < 0){
        velocity.ry() *= -1 * collision_factor;
        position.ry() = 0;
    }
    // dol
    else if (position.ry() + 2*r > scene()->height()){
        velocity.ry() *= -1 * collision_factor;
        position.ry() = scene()->height() - 2*r;
    }

}

void Particle::move()
{
    velocity.ry() += gravity;
    position.ry() += velocity.ry();
    resolve_collisions();

    setPos(position.rx(),position.ry());

    scene()->update();

    // qInfo() << "y: "<<position.ry();
    //   qInfo() << "v:" <<velocity.ry();
}
