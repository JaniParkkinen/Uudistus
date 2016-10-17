#include "Structure.h"
#include "Scene.h"

Structure::Structure(const float x, const float y, Scene* scene, sf::Texture* tex)
    :GameObject(x, y, tex), m_scene(scene)
{}

void Structure::update(const float dt)
{
    sprite->setScale(0.5, 0.5);
    sprite->setPosition(sf::Vector2f(x, y));
}

void Structure::render(sf::RenderTarget* rt)
{
    rt->draw(*sprite);
}