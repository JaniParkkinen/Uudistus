#ifndef STAR_H
#define STAR_H

#include <vector>

#include "Component.h"

//struct Connection;

class Star;

struct Connection
{
    Connection(Star* target, float length)
    {
        this->target = target;
        this->length = length;
    }
    Star* target;
    float length;
};

class Star : public Component
{
public:
    Star(const float energy = 100)
    {
        m_energy = energy;
    }
    bool connect(Star* target);

    void update(float dt)override //const!
    {
        m_energy += dt / 10.f;
    }
    //bool isConnected(Star* target);

//private:
    float m_energyTimer;
    float m_shipTimer;
    float m_energy;
    std::vector<Connection> m_connections;
};

#endif