#pragma once

#include <vector>

#include "GameObject.h"

class Scene
{
public:
    virtual void update(const float dt) = 0;
    virtual void render() = 0;
protected:
    std::vector<GameObject*> gameObjects;
};