#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f position, const int owner, const std::string type, sf::Texture* texture, const float energy)
    :m_position(position),
    m_owner(owner),
    m_type(type),
    m_energy(energy)
{
    if (texture != nullptr)
    {
        m_sprite = new sf::Sprite(*texture);
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

sf::Vector2f GameObject::getPosition()
{
    return m_position;
}

sf::Sprite* GameObject::getSprite()
{
    return m_sprite;
}

float GameObject::getDistanceToPoint(sf::Vector2f point)
{
    return getDistanceToPoint(point.x, point.y);
}

float GameObject::getDistanceToPoint(float x, float y)
{
    float deltaX = getPosition().x - x;
    float deltaY = getPosition().y - y;

    return sqrt(deltaX*deltaX + deltaY*deltaY);
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
