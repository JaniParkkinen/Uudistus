#pragma once

#include "Scene.h"

class GameScene : public Scene
{
public:
    GameScene();
    void update(const float dt)override;
private:
    //std::vector<AIController> ais;
};