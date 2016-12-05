#include "LobbyScene.h"

LobbyScene::LobbyScene(sf::RenderWindow* rw) :
    Scene(rw),
    m_gui(200, 50, 400, 400, 4, 1)
{
    m_gui.createButton("ready", std::bind(&LobbyScene::ready, this), )
}

LobbyScene::~LobbyScene()
{

}

void LobbyScene::update(const float dt)
{

}

void LobbyScene::draw(sf::RenderTarget* rt)
{
    m_gui.draw(rt);


}

void LobbyScene::playerList()
{

}

void LobbyScene::ready()
{

}