#include "liquidsimulation.h"
#include <QVector>
#include <QtMath>
#include <QRandomGenerator>
#include <QSerialPort>

int _fps = 60;
int number_of_particles = 50;

LiquidSimulation::LiquidSimulation()
{
   for(int i = 0 ; i < number_of_particles ; ++i){
    QPointF randomPoint((qreal)(QRandomGenerator::global()->bounded(750) + 30), (qreal)(QRandomGenerator::global()->bounded(550) + 30));
    Particle * particle = new Particle(randomPoint);
    this->particles.push_back(particle);
    this->particles[i]->setId(i);
    this->particles[i]->setGravity(QPointF(0,0));
   }
   serial_port = new SerialPort(this);
   qInfo() << "Connect Arduino";
   connect(serial_port, SIGNAL(dataReceived(QByteArray)), this, SLOT(handleDataReceived(QByteArray)));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(resolve_particle_collisions()));
    timer->start(1000/_fps);


}

LiquidSimulation::~LiquidSimulation()
{
    delete timer;
    delete serial_port;
}


void LiquidSimulation::resolve_particle_collisions()
{
    // Loop through each particle
    for (auto& particlePtr : particles) {
        Particle& particle = *particlePtr;
        for (auto& targetPtr : particles) {
            Particle& target = *targetPtr;

            // Ensure we're not checking the same particle
            if (particle.getId() != target.getId() && particles_touch(particle, target)) {
                // Calculate the distance vector between the particles
                QPointF r = target.getPosition() - particle.getPosition();
                qreal distance = sqrt(QPointF::dotProduct(r, r));

                // Avoid division by zero
                if (distance == 0) {
                    continue; // Skip this iteration to avoid undefined behavior
                }

                // Calculate the overlap distance
                qreal overlapDistance = 2* particle.getR() - distance;

                if (overlapDistance > 0) {
                    // Calculate the correction vector to resolve overlap
                    QPointF overlapDirection = r / distance;
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

void LiquidSimulation::updateGravity(const QByteArray &data)
{
    // Convert QByteArray to QString for easier parsing
    QString dataStr = QString::fromUtf8(data).trimmed();
    QStringList parts = dataStr.split(" ");

    if (parts.size() == 2) {
        bool ok1, ok2;
        qreal newGravityX = parts[0].toDouble(&ok1);
        qreal newGravityY = -parts[1].toDouble(&ok2);

        if (ok1 && ok2) {
            gravity=QPointF(newGravityX,newGravityY);
            for (auto & part : particles){
                part->setGravity(gravity);
                //qDebug() << "zmienilem gravity";
            }
            //qDebug() << "Updated gravity: X =" << gravity.rx() << ", Y =" << gravity.ry();
        } else {
            qDebug() << "Error parsing gravity data:" << dataStr;
        }
    } else {
        qDebug() << "Invalid gravity data format:" << dataStr;
    }
}

void LiquidSimulation::handleDataReceived(const QByteArray &data)
{
    qInfo() << data;
    updateGravity(data);
}



