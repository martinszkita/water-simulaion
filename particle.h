#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>

/*!
 * \brief The Particle class
 *
 * Represents a single object used to simulate fluid dynamics.
 */
class Particle : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    QPointF position; ///< (x,y) position of the middle of the particle
    QPointF velocity; ///< (x,y) velocity of the middle of the particle
    QColor kolor; ///< color of the particle
    QTimer * timer1; ///< timer to refresh particle's parameters every quant of time
    int r; ///< particle's radius
    int id;
public:
    Particle();
    Particle(const Particle & other);
    Particle(QPointF);
    Particle & operator=(const Particle & other);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QRectF boundingRect() const override;
    void resolve_edge_collisions();
    void display_state();
    bool particles_touch(const Particle &  other);

    // setters and getters


    void setR(int newR);
    int getR() const;
    void setPosition(QPointF newPosition);
    QPointF getPosition() const;
    QPointF getVelocity() const;
    void setVelocity(QPointF newVelocity);
    int getId() const;
    void setId(int newId);

public slots:
    void move();

protected:
    void key_pressed(QKeyEvent * event);
};

#endif // PARTICLE_H
