#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>

class Particle : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    QPointF position;
    QPointF velocity;
    QColor kolor;
    int r = 5;
public:
    Particle(const Particle &other);
    Particle(QPointF);
    Particle & operator=(const Particle &other);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QRectF boundingRect() const override;
    void resolve_collisions();
public slots:
    void move();

};

#endif // PARTICLE_H
