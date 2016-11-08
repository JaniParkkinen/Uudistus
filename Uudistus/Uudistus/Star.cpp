#include "Star.h"
#include "GameObject.h"
//#include "UudistusMath.h"

//Star::Star(const sf::Vector2f position, const int owner, sf::Texture* starTexture/*this from resource manager*/, const float energy)
//    :GameObject(position, owner, "star", starTexture, energy)
//{
//
//}

bool Star::connect(Star* target)
{
    if (target == this)
        return false;

    for (Connection c : m_connections)
    {
        if (c.target == target)
            return false;
    }

    sf::Vector2f delta = target->getGameObject()->getPosition() - getGameObject()->getPosition();
    float length = sqrt(delta.x*delta.x + delta.y*delta.y);

    m_connections.push_back(Connection(target, length));
    target->connect(this);
    return true;
}