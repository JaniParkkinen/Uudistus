#include "LobbyScene.h"
#include "SceneManager.h"
#include "NetworkManager.h"

LobbyScene::LobbyScene(sf::RenderWindow* rw, SceneManager* sm) :
    Scene(rw, sm),
    m_gui(200, 50, 400, 400, 4, 1)
{
	NetworkManager::instance()->setSceneManager(sm);
	readyDown.loadFromFile("assets/ready_down.png");
	readyUp.loadFromFile("assets/ready_up.png");
	readyHover.loadFromFile("assets/ready_hover.png");
	discDown.loadFromFile("assets/disconnect_down.png");
	discUp.loadFromFile("assets/disconnect_up.png");
	discHover.loadFromFile("assets/disconnect_hover.png");

	m_total_time = 0;

	m_rw = rw;
	m_sm = sm;

	
	m_gui.createButton("ready", std::bind(&LobbyScene::ready, this), &readyUp, &readyDown, &readyHover);
	m_gui.createButton("disconnect", std::bind(&LobbyScene::disconnect, this), &discUp, &discDown, &discHover);
}

LobbyScene::~LobbyScene()
{

}

void LobbyScene::update(const float dt)
{
	if (m_input->mousePressed(MouseButton::Left))
	{
		sf::Vector2f mPos = m_input->getMousePos();
		printf_s("mouse position: %f, %f\n", mPos.x, mPos.y);
	}

	if (m_rw != nullptr)
		m_input->update(dt, m_rw);


	m_total_time = +dt;
	m_gui.update();
}

void LobbyScene::draw(sf::RenderTarget* rt)
{

	//draw GUI
    m_gui.draw(rt);
}

void LobbyScene::playerList()
{
	
}

void LobbyScene::readyCheck()
{

}

void LobbyScene::ready()
{
		//m_sm->changeScene(1);
		NetworkManager::instance()->setReady(true);
        m_gui.removeElement("ready");
}

void LobbyScene::disconnect()
{
	printf_s("Player disconnected\n");
}

