#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>

class Particle : public QGraphicsItem
{
private:
    int pos_x;
    int pos_y;
    int h_x= 15;
    int h_y= 15;
public:
    Particle();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QRectF boundingRect() const override;
    void move();


};

#endif // PARTICLE_H
