#include "GameScene.h"
#include "Structure.h"

GameScene::GameScene(sf::RenderWindow* window)
    :Scene(window), window(window)
{
    tex.loadFromFile("assets/planet.png");
    //sf::Sprite* spr = new sf::Sprite(tex);
    for (int i = 0; i < 10; i++)
    {
        gameObjects.push_back(new Structure(100.f * i, 10   0.f, this, &tex));
    }
}

void GameScene::update(float dt)
{
    Scene::update(dt);
    for (auto o : gameObjects)
    {
        sf::Vector2f pos0 = o->getPosition();
        float dis = sqrt(pos0.x*pos0.x + pos0.y*pos0.y);
        float dir = atan2f(pos0.y, pos0.x) + dt / 10.f;
        o->setPosition(cos(dir) * dis, sin(dir) * dis);
    }


}

void GameScene::render(sf::RenderTarget* rt)
{
    Scene::render(rt);
}