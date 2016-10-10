#pragma once

#include <SFML\Graphics.hpp>

class GameObject
{
public:
    GameObject(const float x, const float y, const sf::Sprite* sprite = nullptr);

    virtual void update(float dt) = 0;

protected:
    float x, y;
    sf::Sprite* sprite;
};