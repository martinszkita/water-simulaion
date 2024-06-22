#include "liquidsimulation.h"
#include <QVector>
#include <QtMath>

int _fps = 60;
int number_of_particles = 2;

LiquidSimulation::LiquidSimulation()
{
//    for(int i = 0 ; i < number_of_particles ; ++i){
//        Particle *particle = new Particle();
//        this->particles.push_back(particle);
//        this->particles[i]->setId(i);
//    }
    Particle *particle = new Particle(QPointF(60,20));
    particle->setId(1);
    this->particles.push_back(particle);


    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(resolve_particle_collisions()));
    timer->start(1000/_fps);

}

LiquidSimulation::~LiquidSimulation()
{
    qDebug() << "koniec liquid sumulation";
}


void LiquidSimulation::resolve_particle_collisions()
{
    const qreal restitution = 0.8; // Coefficient of restitution for elastic collisions (adjust as needed)

    // Loop through each particle
    for (auto& particlePtr : particles) {
        Particle& particle = *particlePtr;
        for (auto& targetPtr : particles) {
            Particle& target = *targetPtr;

            if (particle.getId() != target.getId() && particles_touch(particle, target)) {
                qDebug() << "Collision detected between particle" << particle.getId() << "and" << target.getId();

                // Calculate relative position vector and relative velocity vector
                QPointF r = target.getPosition() - particle.getPosition();
                QPointF v = target.getVelocity() - particle.getVelocity();

                // Calculate dot products
                qreal r_dot_v = QPointF::dotProduct(r, v);
                qreal r_dot_r = QPointF::dotProduct(r, r);

                // Ensure r_dot_r is not zero to prevent division by zero
                if (r_dot_r == 0) {
                    continue; // Skip this collision to avoid undefined behavior
                }

                // Calculate impulse along the normal direction
                qreal impulse_scalar = (-(1 + restitution) * r_dot_v) / r_dot_r;
                QPointF impulse = impulse_scalar * r;

                // Update velocities
                particle.setVelocity(particle.getVelocity() + impulse);
                target.setVelocity(target.getVelocity() - impulse);

                // Resolve overlap (optional, adjust positions)
                qreal overlapDistance = particle.getR() + target.getR() - sqrt(r_dot_r);
                if (overlapDistance > 0) {
                    // Calculate overlap direction and correction vector
                    QPointF overlapDirection = r / sqrt(r_dot_r);
                    QPointF correction = overlapDistance * overlapDirection * 0.5;

                    // Move particles apart to resolve overlap
                    particle.setPosition(particle.getPosition() - correction);
                    target.setPosition(target.getPosition() + correction);
                }
            }
        }
    }
}


bool LiquidSimulation::particles_touch(const Particle& particle, const Particle& target)
{
    qreal distanceSquared = QPointF::dotProduct(target.getPosition() - particle.getPosition(), target.getPosition() - particle.getPosition());
    qreal radiusSquared = (particle.getR() + target.getR()) * (particle.getR() + target.getR());
    return distanceSquared <= radiusSquared;
}


