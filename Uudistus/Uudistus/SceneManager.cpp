#include "SceneManager.h"
#include "LobbyScene.h"
#include "GameScene.h"

SceneManager::SceneManager(sf::RenderWindow* rw)
	:m_rw(rw),
	m_mutex()
{
	m_sceneToChange = -1;
}

SceneManager::~SceneManager()
{

}

void SceneManager::update(const float dt)
{
	m_mutex.lock();

	if (m_sceneToChange != -1)
	{
		switch (m_sceneToChange)
		{
		case 0:
		{
			delete currentScene;
			currentScene = new LobbyScene(m_rw, this);
			m_sceneToChange = -1;
			break;
		}
		case 1:
		{
			delete currentScene;
			currentScene = new GameScene(m_rw, this);
			m_sceneToChange = -1;
			break;
		}
		default:
			break;
		}
	}
	currentScene->update(dt);
	m_mutex.unlock();
}

void SceneManager::draw(sf::RenderTarget* rt)
{
	m_mutex.lock();
	currentScene->draw(rt);
	m_mutex.unlock();
}

void SceneManager::changeScene(int id)
{
	//m_mutex.lock();
	m_sceneToChange = id;
	//m_mutex.unlock();
}