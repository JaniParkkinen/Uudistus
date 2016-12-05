#include "LobbyScene.h"
#include "SceneManager.h"
#include "GameScene.h"

LobbyScene::LobbyScene(sf::RenderWindow* rw, SceneManager* sm) :
    Scene(rw, sm),
    m_gui(200, 50, 400, 400, 4, 1)
{

	readyDown.loadFromFile("assets/ready_down.png");
	readyUp.loadFromFile("assets/ready_up.png");
	readyHover.loadFromFile("assets/ready_hover.png");

	m_total_time = 0;

	m_rw = rw;
	m_sm = sm;

	m_gui.createButton("ready", std::bind(&LobbyScene::ready, this), &readyUp, &readyDown, &readyHover);
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

	m_gui.update();

	m_total_time = +dt;
}

void LobbyScene::draw(sf::RenderTarget* rt)
{

	//draw GUI
    m_gui.draw(rt);
}

void LobbyScene::playerList()
{

}

void LobbyScene::ready()
{
	m_sm->changeScene(new GameScene(m_rw, m_sm));
}