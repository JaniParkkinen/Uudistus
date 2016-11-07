#include "Star.h"

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
    m_connections.push_back(Connection(target, getDistanceToPoint(target->getPosition())));
    target->connect(this);
    return true;
}