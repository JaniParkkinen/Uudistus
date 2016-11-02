#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

//#include "GameObject.h"
#include "InputManager.h"

//class GameObject;

class Scene
{
public:

    Scene(sf::RenderWindow* rw)
        :input(new InputManager())
    {}

    virtual void update(const float dt) = 0
    {
        if(rw != nullptr)
            input->update(dt, rw);
    }

    virtual void render(sf::RenderTarget* rt) = 0;

    void setWindow(sf::RenderWindow* renderWindow)
    {
        rw = renderWindow;
    }

    InputManager* getInputManager()
    {
        return input;
    }

protected:
    //std::vector<GameObject*> gameObjects;
    InputManager* input;
    sf::RenderWindow* rw;
};