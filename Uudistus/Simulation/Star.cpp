#include "Star.h"
#include "GameObject.h"

Star::Star(GameObject* parent, const float energy)
{
    m_gameObject = parent;
    m_energy = energy;
}

Star::~Star()
{
    for (Connection* c : m_connections)
    {
        delete c;
    }
}

void Star::update(const float dt)
{
    m_energy += dt / 10.f;
}

const std::vector<Connection*>& Star::getConnections()
{
    return m_connections;
}

bool Star::connect(Star* target)
{
    if (target == this)
        return false;

    for (Connection* c : m_connections)
    {
        if (c->target == target)
            return false;
    }

    sf::Vector2f delta = target->getGameObject()->getPosition() - getGameObject()->getPosition();
    float length = sqrt(delta.x*delta.x + delta.y*delta.y);

    m_connections.push_back(new Connection(target, length));
    target->connect(this);
    return true;
}