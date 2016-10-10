#include "GameScene.h"
#include "Structure.h"

GameScene::GameScene()
{
    sf::Texture tex;
    tex.loadFromFile("assets/planet.png");
    sf::Sprite* spr = new sf::Sprite(tex);
    for (int i = 0; i < 10; i++)
    {
        gameObjects.push_back(new Structure(10.f * i, 10.f, spr));
    }
}