#include "particle.h"
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <qrandom.h>
#include <QPointF>
#include <QKeyEvent>

int fps = 60;
int rr = 5;
float collision_factor = 1;
qreal initial_pos_x = 0;
qreal initial_pos_y = 0;
qreal initial_vel_x = 0.1;
qreal initial_vel_y = 0.1;
qreal gravity_x = 0.1;
qreal gravity_y = 0.1;
QColor color = Qt::red;

QPointF initial_velocity = QPointF(initial_vel_x,initial_vel_y);
QPointF gravity = QPointF(gravity_x,gravity_y);
/*!
 * \brief Particle::Particle
 * Particle class generator for random initial velocity and position
 */
void Particle::setR(int newR)
{
    r = newR;
}

int Particle::getR() const
{
    return r;
}

void Particle::setPosition(QPointF newPosition)
{
    position = newPosition;
}

QPointF Particle::getPosition() const
{
    return position;
}

QPointF Particle::getVelocity() const
{
    return velocity;
}

void Particle::setVelocity(QPointF newVelocity)
{
    velocity = newVelocity;
}

int Particle::getId() const
{
    return id;
}

void Particle::setId(int newId)
{
    id = newId;
}

Particle::Particle()
{
    qInfo() << "konstruktor bezparam";
    this->kolor = color;
    this->r=rr;

    if (scene()) {
        qreal sceneWidth = scene()->width();
        qreal sceneHeight = scene()->height();

        this->velocity=initial_velocity;
        this->position = QPointF((qreal)(QRandomGenerator::global()->bounded(sceneWidth) - 10),
                                 (qreal)(QRandomGenerator::global()->bounded(sceneHeight) - 10));
    }

    else {
        qInfo() << "scene null ptr";
    }
    qInfo() << "bez:" << position;
    setPos(this->position);
}


/*!
 * \brief Particle::Particle
 *
 * Particle class constructor. Sets up the particle's parameters.
 * Starts the timer and so the particle movement.
 * \param param1 QPointF pos, which is the initial position
 *
 * @return Particle class object
 */

Particle::Particle(QPointF pos): position(pos)
{
    qInfo() << "konstrukor param:" << position;
    this->kolor = color;
    this->r=rr;
    this->velocity=initial_velocity;

    ///< timer setup for moving particle
//    timer1 = new QTimer();
//    connect(timer1,SIGNAL(timeout()),this,SLOT(move()));
//    timer1->start(1000/fps);
    setPos(this->position);
    qInfo() << "konstrukor param po setPos:" << position;
}
/*!
 * \brief Particle::paint
 * Function paints a circule with the given position, color and brush
 * \param painter
 * \param option
 * \param widget
 */
void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QPen pen;
    pen.setWidth(2);
    pen.setColor(this->kolor);
    painter->setPen(pen);
    painter->setBrush(this->kolor); // wypelnienie
    qInfo() << "pozycja: "<< this->position;
    painter->drawEllipse(this->position,this->r*2,this->r*2);
}
/*!
 * \brief Particle::boundingRect
 * Creates a rectangle to bound a circular particle
 * \return boundingRect
 */
QRectF Particle::boundingRect() const
{
    return QRectF();
}

/*!
 * \brief Particle::resolve_collisions
 * Function handles a partcile hitting the edge of the scene.
 */
void Particle::resolve_edge_collisions(){

    if (position.rx()   < r){
        velocity.rx() *= -1 * collision_factor;
        position.rx() = r;
        //qDebug() << "lewa sciana";
    }
    else if(position.rx()+r  >= scene()->width()/2){
        velocity.rx() *= -1*collision_factor;
        position.rx() = scene()->width()/2-r;
        //qDebug() << "prawa sciana";
    }
    if(position.ry() - r  <= 0){
        velocity.ry() *= -1 * collision_factor;
        position.ry() = r;
        //qDebug() << "gorna sciana";
    }
    else if (position.ry() +r > scene()->height()/2){
        velocity.ry() *= -1 * collision_factor;
        position.ry() = scene()->height()/2-r;
        //qDebug() << "dolna sciana";
    }
}


/*!
 * \brief Particle::display_state
 * Helper function to show the current position and velocity of the particle.
 */
void Particle::display_state()
{
    qInfo() << "------------------------------------";
    //qInfo() << "particle: " << id;
    //qInfo() << "x:" << position.rx()<<" y: "<<position.ry();
    qInfo() << "v_x: " <<velocity.rx()<<" v_y: "<<velocity.ry();
}

bool Particle::particles_touch(const Particle & other)
{
    return (getPosition().rx() - other.getPosition().rx()) * (getPosition().rx() - other.getPosition().rx()) + (getPosition().ry() - other.getPosition().ry()) * (getPosition().ry() - other.getPosition().ry()) <= 4*getR()*getR();
}

/*!
 * \brief Particle::move
 * Updates the particle's position every (set in the timer) quant of time
 * and then refreshes the scene.
 */
void Particle::move()
{
    velocity += gravity;
    position += velocity;
    resolve_edge_collisions();

    setPos(position);
    scene()->update();
    //display_state();
}
