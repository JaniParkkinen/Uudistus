#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void update(const float dt);
	void draw(sf::RenderTarget* rt);
	void changeScene(Scene* newScene);

private:
	Scene* currentScene;

};


#endif