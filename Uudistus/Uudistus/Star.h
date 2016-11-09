#ifndef STAR_H
#define STAR_H

#include <vector>

#include "Component.h"

class Star;

struct Connection
{
    Connection::Connection(Star* target, float length)
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
    Star(GameObject* parent, const float energy = 100);
    ~Star();
    bool connect(Star* target);

    void update(const float dt)override;

    const std::vector<Connection*>& getConnections();
    //bool isConnected(Star* target);

private:
    float m_energyTimer;
    float m_shipTimer;
    float m_energy;
    std::vector<Connection*> m_connections;
};

#endif