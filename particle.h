#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>

class Particle : public QWidget, QGraphicsItem
{
    Q_OBJECT
public:
    Particle(QWidget * parent);
    virtual void paintEvent(QPaintEvent * pEvent) override;
};

#endif // PARTICLE_H
