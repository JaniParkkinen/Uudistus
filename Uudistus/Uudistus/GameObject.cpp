#include "GameObject.h"

GameObject::GameObject(const int ID, const sf::Vector2f position, float size, const int owner, const std::string type, sf::Texture* texture, const float energy)
    :m_ID(ID),
    m_position(position),
    m_owner(owner),
    m_type(type),
    m_energy(energy),
    m_size(size)
{
    if (texture != nullptr)
    {
        m_sprite = new sf::Sprite(*texture);
        m_sprite->setPosition(position);
        float scale = m_size / texture->getSize().x;
        m_sprite->setScale(scale, scale);
        m_sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
    }
}

void GameObject::setPosition(sf::Vector2f pos)
{
    setPosition(pos.x, pos.y);
}

void GameObject::setPosition(float x, float y)
{
    this->m_position.x = x;
    this->m_position.y = y;
}

void GameObject::setSize(float size)
{
    m_size = size;
}

sf::Vector2f GameObject::getPosition()
{
    return m_position;
}

sf::Sprite* GameObject::getSprite()
{
    return m_sprite;
}

float GameObject::getSize()
{
    return m_size;
}

float GameObject::getDistanceToPoint(sf::Vector2f point)
{
    return getDistanceToPoint(point.x, point.y);
}

//float GameObject::getDistanceToPoint(ud::Vec2 point)
//{
//    return getDistanceToPoint(point.x, point.y);
//}

float GameObject::getDistanceToPoint(float x, float y)
{
    float deltaX = getPosition().x - x;
    float deltaY = getPosition().y - y;

    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

int GameObject::getID()
{
    return m_ID;
}

//void GameObject::update(const float dt)
//{
//    m_sprite->setScale(0.5, 0.5);
//    m_sprite->setPosition(m_position);
//}

//void GameObject::render(sf::RenderTarget* rt)
//{
//    rt->draw(*m_sprite);
//}
