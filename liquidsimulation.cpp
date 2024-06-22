#include "liquidsimulation.h"
#include <QVector>
#include <QtMath>
#include <QPair>

int _fps = 60;
int number_of_particles = 2;

QVector<Particle *> LiquidSimulation::getParticles() const
{
    return particles;
}

void LiquidSimulation::setParticles(const QVector<Particle *> &newParticles)
{
    particles = newParticles;
}

LiquidSimulation::LiquidSimulation()
{
    for(int i = 0 ; i < number_of_particles ; ++i){
        Particle *particle = new Particle(QPointF(300,200)); // uzywac innego konstruktora?
        this->particles.push_back(particle);
        this->particles[i]->setId(i);
    }

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(resolve_particle_collisions()));
    timer->start(1000/_fps);

    for(int  i = 0 ; i < number_of_particles; i++){

        QTimer * move_timer = new QTimer(this);
        move_timers.push_back(move_timer);
        move_timers[i]->start();
    }
}

LiquidSimulation::~LiquidSimulation()
{
    qDebug() << "koniec liquid sumulation";
    qDeleteAll(particles);
    delete timer;
}


void LiquidSimulation::resolve_particle_collisions()
{
    QVector<QPair<Particle *, Particle *>> collided_particles_pairs;

    for(auto & particlePtr : particles){
        Particle & particle = * particlePtr;
        for(auto & targetPtr : particles){
            Particle & target = * targetPtr;
            if (particle.getId() != target.getId() && particle.particles_touch(target)){
                //qDebug() <<"kolizja";
                collided_particles_pairs.push_back({&particle,&target});

                double x1 = particle.getPosition().rx();
                double y1 = particle.getPosition().ry();
                double x2 = target.getPosition().rx();
                double y2 = target.getPosition().ry();
                double r = target.getR();

                // distance between both particle centers
                auto distance = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

                // common section length
                auto overlap = distance - r*2;

                QPointF new_particle_position = QPointF((x1-overlap*(x1-x2) / distance),(y1-overlap*(y1-y2) / distance));
                QPointF new_target_position = QPointF((x1+overlap*(x1-x2) / distance),(y1+overlap*(y1-y2) / distance));


                // static collision
                particle.setPosition(new_particle_position);
                target.setPosition(new_target_position);
            }
        }
    }


    for( auto & pair : collided_particles_pairs){
        Particle & particle = *pair.first;
        Particle & target = *pair.second;

        double x1 = particle.getPosition().rx();
        double y1 = particle.getPosition().ry();
        double x2 = target.getPosition().rx();
        double y2 = target.getPosition().ry();

        double distance = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        //qInfo() << "distance:" << distance;

        // calculate normal (line connecting two particle centers)
        double normal_x = (x1-x2)/ distance;
        double normal_y = (y1-y2)/ distance;

        // calculate tangent (perpendicular to normal in the point of particle touch)
        double tangent_x = -normal_y;
        double tangent_y = normal_x;

        // calculate dot product on tangent
        double dp_tangent_particle = particle.getVelocity().rx()*tangent_x + particle.getVelocity().ry() * tangent_y;
        double dp_tangent_target = target.getVelocity().rx()*tangent_x + target.getVelocity().ry() * tangent_y;

        // dot product normal
        double dp_normal_particle = particle.getVelocity().rx()*normal_x + particle.getVelocity().ry() * normal_y;
        double dp_normal_target = target.getVelocity().rx()*normal_x + target.getVelocity().ry() * normal_y;

        // velocities with equal masses (ZZP)
        double m1 = dp_normal_target;
        double m2 = dp_normal_particle;

        particle.setVelocity(QPointF(tangent_x * dp_tangent_particle + m1 * normal_x, tangent_y * dp_tangent_particle + m1 * normal_y  ));
        target.setVelocity(QPointF(tangent_x * dp_tangent_target + m2 * normal_x, tangent_y * dp_tangent_target + m2 * normal_y  ));

//        qInfo() << " -------";
//        qInfo() << "ustawiam particle";
//        qInfo() << "v_x: " <<particle.getVelocity().rx()<<" v_y: "<<particle.getVelocity().ry();
//        qInfo() << "ustawiam target";
//        qInfo() << "v_x: " <<target.getVelocity().rx()<<" v_y: "<<target.getVelocity().ry();
    }
}


