#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::update(const float dt)
{
	currentScene->update(dt);
}

void SceneManager::draw(sf::RenderTarget* rt)
{
	currentScene->draw(rt);
}

void SceneManager::changeScene(Scene* newScene)
{
	delete currentScene;
	currentScene = newScene;
}