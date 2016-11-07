#ifndef STAR_H
#define STAR_H

#include "GameObject.h"

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

class Star : public GameObject
{
public:
    Star(const int ID, const sf::Vector2f position, const int owner, sf::Texture* starTexture/*this from resource manager*/, const float energy = 100)
        :GameObject(ID, position, owner, "star", starTexture, energy)
    {

    }
    bool connect(Star* target);

//private:
    float m_energyTimer;
    float m_shipTimer;
    std::vector<Connection> m_connections;
};

#endif