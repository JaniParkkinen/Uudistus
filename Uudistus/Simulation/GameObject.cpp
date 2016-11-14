#include "GameObject.h"
//#include "Component.h"
#include <math.h>
#include <string>

GameObject::GameObject(const int ID, const float x, const float y, float size, const int owner, const std::string type, const float energy)
    :m_ID(ID),
    m_x(x),
    m_y(y),
    m_owner(owner),
    m_type(type),
    m_energy(energy),
    m_size(size)
{
}

GameObject::~GameObject()
{
    for (Component* c : m_components)
    {
        delete c;
    }
}

void GameObject::update(const float dt)
{
    for (Component* comp : m_components)
    {
        comp->update(dt);
    }
}

void GameObject::setPosition(float x, float y)
{
    this->m_x = x;
    this->m_y = y;
}

void GameObject::setSize(float size)
{
    m_size = size;
}

void GameObject::setEnergy(float energy)
{
    m_energy = energy;
}

void GameObject::setOwner(int owner)
{
    m_owner = owner;
}

//########## GET

const float GameObject::getX()const
{
    return m_x;
}

const float GameObject::getY()const
{
    return m_y;
}

float GameObject::getSize()
{
    return m_size;
}

float GameObject::getEnergy()
{
    return m_energy;
}

int GameObject::getOwner()
{
    return m_owner;
}

std::string GameObject::getType()
{
    return m_type;
}

//float GameObject::getDistanceToPoint(ud::Vec2 point)
//{
//    return getDistanceToPoint(point.x, point.y);
//}

float GameObject::getDistanceToPoint(float x, float y)
{
    float deltaX = m_x - x;
    float deltaY = m_y - y;

    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

const int GameObject::getID()const
{
    return m_ID;
}

void GameObject::destroy()
{
    m_isDestroyed = true;
}

bool GameObject::isDestroyed()
{
    return m_isDestroyed;
}