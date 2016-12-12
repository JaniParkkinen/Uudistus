#include "Star.h"
#include "GameObject.h"

Star::Star(GameObject* parent, const float energy)
{
    printf_s("Star constructor\n");
    m_gameObject = parent;
    parent->setEnergy(energy);
    m_level = 1;
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
    if (getGameObjectConst()->getOwner() != 0)
    {
        getGameObject()->setEnergy(getGameObject()->getEnergy() + m_level);
    }
}

const std::vector<Connection*>& Star::getConnections()
{
    return m_connections;
}

bool Star::connect(const Star* target)
{
    if (target == this)
        return false;

    for (Connection* c : m_connections)
    {
        if (c->target == target)
            return false;
    }

    float deltaX = target->getGameObjectConst()->getX() -getGameObject()->getX();
    float deltaY = target->getGameObjectConst()->getY() - getGameObject()->getY();
    float length = sqrt(deltaX*deltaX + deltaY*deltaY);

    m_connections.push_back(new Connection(target, length));
    return true;
}

void Star::upgrade()
{
    if (m_gameObject->getEnergy() > m_level * 250)
    {
        m_gameObject->setEnergy(m_gameObject->getEnergy() - m_level++ * 250);
    }
}