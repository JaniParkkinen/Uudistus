#include "Structure.h"

Structure::Structure(const float x, const float y, const sf::Sprite* sprite)
    :GameObject(x, y, sprite)
{}

void Structure::update(const float dt)
{
    sprite->setPosition(sf::Vector2f(x, y));
}