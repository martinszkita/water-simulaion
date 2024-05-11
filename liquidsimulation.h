#ifndef LIQUIDSIMULATION_H
#define LIQUIDSIMULATION_H

#include "particle.h"
#include <QVector>
#include <QTimer>
#include <QObject>
class LiquidSimulation : public QObject
{
    Q_OBJECT
private:
    QTimer * timer;
public:
    QVector<Particle*> particles;
    LiquidSimulation();
    ~LiquidSimulation();
    bool particles_collide(Particle & particle1, Particle & particle2);
public slots:
    void resolve_particle_collisions();
};

#endif // LIQUIDSIMULATION_H
