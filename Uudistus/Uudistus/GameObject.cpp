#include "GameObject.h"

GameObject::GameObject(const float x, const float y, sf::Texture* tex)
    :y(y), x(x)
{
    if (tex != nullptr)
    {
        sprite = new sf::Sprite(*tex);
    }
}

void GameObject::setPosition(sf::Vector2f pos)
{
    setPosition(pos.x, pos.y);
}

void GameObject::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

sf::Vector2f GameObject::getPosition()
{
    return sf::Vector2f(x, y);
}