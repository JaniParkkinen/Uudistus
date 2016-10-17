#pragma once

#include "Scene.h"

class GameScene : public Scene
{
public:
    GameScene(sf::RenderWindow* window);
    void update(const float dt)override;
    void render(sf::RenderTarget* rt)override;
private:
    sf::Texture tex;
    sf::RenderWindow* window;
public: 
    

    //std::vector<AIController> ais;
};