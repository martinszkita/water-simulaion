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
    QVector<QTimer *> move_timers;
    QVector<Particle*> particles;

public:

    LiquidSimulation();
    ~LiquidSimulation();
    bool particles_collide(Particle & particle1, Particle & particle2);
    QVector<Particle *> getParticles() const;
    void setParticles(const QVector<Particle *> &newParticles);

public slots:
    void resolve_particle_collisions();
};

#endif // LIQUIDSIMULATION_H
