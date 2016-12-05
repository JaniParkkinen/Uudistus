#ifndef SCENE_H
#define SCENE_H

#include <SFML\Graphics.hpp>

//#include "GameObject.h"
#include "InputManager.h"

//class GameObject;

class SceneManager;

class Scene
{
public:

	Scene(sf::RenderWindow* rw, SceneManager* sm)
		:m_input(InputManager::instance()),
		m_sm(sm)

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
	SceneManager* m_sm;
	//NetworkManager* m_nm;
};

#endif