#include "GameScene.h"
#include "Star.h"

GameScene::GameScene(sf::RenderWindow* window)
    :Scene(window), window(window)
{
    tex.loadFromFile("assets/planet.png");
}

void GameScene::update(float dt)
{
    Scene::update(dt);
}

void GameScene::render(sf::RenderTarget* rt)
{
    Scene::render(rt);
    rt->draw(sf::Sprite(tex));
}

void GameScene::generateLevel()
{
    m_world.push_back(new Star());
}