#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include <mutex>

class SceneManager
{
public:
	SceneManager(sf::RenderWindow* rw);
	~SceneManager();

	void update(const float dt);
	void draw(sf::RenderTarget* rt);
	void changeScene(int id);

private:
	int m_sceneToChange;
	Scene* currentScene;
	Scene* newScene;
	std::mutex m_mutex;
	sf::RenderWindow* m_rw;
};


#endif