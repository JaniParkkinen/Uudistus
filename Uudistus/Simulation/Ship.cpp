#include "Ship.h"
#include "GameObject.h"

Ship::Ship(GameObject* parent, GameObject* target, float speed)
{
    m_gameObject = parent;
    m_target = target;
    m_speed = speed;

    sf::Vector2f delta = m_gameObject->getPosition() - m_target->getPosition();
    m_gameObject->getSprite()->setRotation(atan2(delta.y, delta.x));
}

void Ship::update(const float dt)
{
    GameObject* go = getGameObject();

    sf::Vector2f delta = m_target->getPosition() - go->getPosition();
    float distance = sqrt(delta.x*delta.x + delta.y*delta.y);
    

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
        delta.x /= distance;
        delta.y /= distance;

        delta.x *= m_speed * dt;
        delta.y *= m_speed * dt;

        go->setPosition(go->getPosition() + delta);

        go->getSprite()->setPosition(go->getPosition());

    }
}