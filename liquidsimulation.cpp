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

    Particle *particle2 = new Particle(QPointF(50,300));
    particle2->setId(2);
    this->particles.push_back(particle2);

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
    for(auto & particlePtr : particles){
        Particle & particle = * particlePtr;
        for(auto & targetPtr : particles){
            Particle & target = * targetPtr;
            if (particle.getId() != target.getId() && particle.particles_touch(target)){
                qDebug() <<"kolizja";
            }
        }
    }
}

