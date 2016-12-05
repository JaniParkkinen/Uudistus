#ifndef SCENE_H
#define SCENE_H

#include <SFML\Graphics.hpp>

//#include "GameObject.h"
#include "InputManager.h"

//class GameObject;

class Scene
{
public:

    Scene(sf::RenderWindow* rw)
        :m_input(InputManager::instance())
    {}

    virtual void update(const float dt) = 0;

    virtual void draw(sf::RenderTarget* rt) = 0;

    void setWindow(sf::RenderWindow* renderWindow)
    {
        m_rw = renderWindow;
    }

    InputManager* getInputManager()
    {
        return m_input;
    }

protected:
    //std::vector<GameObject*> gameObjects;
    InputManager* m_input;
    sf::RenderWindow* m_rw;
};

#endif