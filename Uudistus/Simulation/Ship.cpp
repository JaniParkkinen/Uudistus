#include "Ship.h"
#include "GameObject.h"
#include <math.h>

Ship::Ship(GameObject* parent, GameObject* target, float speed)
{
    m_gameObject = parent;
    m_target = target;
    m_speed = speed;

}

void Ship::update(const float dt)
{
    GameObject* go = getGameObject();

    float deltaX = m_target->getX() - go->getX();
    float deltaY = m_target->getY() - go->getY();
    float distance = sqrt(deltaX*deltaX + deltaY*deltaY);
    

    if (distance < m_speed)
    {
        //collision!
        
        if (m_target->getOwner() == go->getOwner())
        {
            m_target->setEnergy(m_target->getEnergy() + go->getEnergy());
        }
        else
        {
            m_target->setEnergy(m_target->getEnergy() - go->getEnergy());
            if (m_target->getEnergy() < 0)
            {
                m_target->setEnergy(-m_target->getEnergy());
                m_target->setOwner(go->getOwner());
            }
        }
        go->destroy();
    }
    else
    {
        //move
        deltaX /= distance;
        deltaY /= distance;

        deltaX *= m_speed * dt;
        deltaY *= m_speed * dt;

        go->setPosition(go->getX() + deltaX, go->getY() + deltaY);

    }
}