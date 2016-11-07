#pragma once

#include "UudistusMath.h"

class GameObject;

class Component
{
public:
    //Component() {};
    virtual void update(float dt)=0;

    GameObject* getGameObject();

private:
    GameObject* m_gameObject;
};