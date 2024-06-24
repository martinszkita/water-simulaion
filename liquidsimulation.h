/**
 * @file liquidsimulation.h
 * @brief Plik nagłówkowy klasy LiquidSimulation.
 *
 * Plik zawiera deklarację klasy LiquidSimulation, która jest odpowiedzialna za
 * symulację cieczy za pomocą cząsteczek. Klasa obsługuje kolizje cząsteczek,
 * odbieranie danych z portu szeregowego oraz aktualizację siły grawitacji.
 */

#ifndef LIQUIDSIMULATION_H
#define LIQUIDSIMULATION_H

#include "particle.h"
#include <QVector>
#include <QTimer>
#include <QObject>
#include "serialport.h"

/**
 * @class LiquidSimulation
 * @brief Klasa symulująca ciecz za pomocą cząsteczek.
 *
 * Klasa LiquidSimulation zarządza cząsteczkami, obsługuje ich kolizje,
 * odbiera dane z portu szeregowego i aktualizuje siłę grawitacji.
 */
class LiquidSimulation : public QObject
{
    Q_OBJECT
private:
    QTimer * timer;          /**< Timer do zarządzania czasem symulacji. */
    SerialPort * serial_port;/**< Port szeregowy do odbierania danych. */

public:
    QVector<Particle*> particles; /**< Wektor przechowujący wskaźniki do cząsteczek. */
    QPointF gravity;              /**< Siła grawitacji działająca na cząsteczki. */

    /**
     * @brief Konstruktor domyślny.
     */
    LiquidSimulation();

    /**
     * @brief Destruktor.
     */
    ~LiquidSimulation();

    /**
     * @brief Sprawdza, czy dwie cząsteczki kolidują.
     * @param particle1 Pierwsza cząsteczka.
     * @param particle2 Druga cząsteczka.
     * @return True, jeśli cząsteczki kolidują, false w przeciwnym razie.
     */
    bool particles_collide(Particle & particle1, Particle & particle2);

    /**
     * @brief Sprawdza, czy jedna cząsteczka dotyka drugiej.
     * @param particle Cząsteczka sprawdzająca.
     * @param target Cząsteczka docelowa.
     * @return True, jeśli cząsteczki się dotykają, false w przeciwnym razie.
     */
    bool particles_touch(const Particle& particle, const Particle& target);

public slots:
    /**
     * @brief Obsługuje kolizje cząsteczek.
     */
    void resolve_particle_collisions();

    /**
     * @brief Obsługuje odbieranie danych z portu szeregowego.
     * @param data Otrzymane dane w postaci QByteArray.
     */
    void handleDataReceived(const QByteArray &data);

    /**
     * @brief Aktualizuje siłę grawitacji na podstawie otrzymanych danych.
     * @param data Otrzymane dane w postaci QByteArray.
     */
    void updateGravity(const QByteArray &data);
};

#endif // LIQUIDSIMULATION_H
