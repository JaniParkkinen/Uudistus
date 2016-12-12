#ifndef STAR_H
#define STAR_H

#include <vector>

#include "Component.h"

class Star;

struct Connection
{
    Connection::Connection(const Star* target, const float length)
        : target(target),
        length(length)
    {

    }
    const Star* target;
    const float length;
};

class Star : public Component
{
public:
    Star(GameObject* parent, const float energy = 100);
    ~Star();
    bool connect(const Star* target);
    void upgrade();

    void update(const float dt)override;

    const int getLevel()const;

    const std::vector<Connection*>& getConnections();
    //bool isConnected(Star* target);

private:
    float m_energyTimer;
    float m_shipTimer;
    int m_level;
    std::vector<Connection*> m_connections;
};

#endif