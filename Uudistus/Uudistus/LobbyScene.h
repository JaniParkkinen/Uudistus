#ifndef LOBBY_SCENE_H
#define LOBBY_SCENE_H

#include "Scene.h"
#include "GuiArea.h"

class LobbyScene : public Scene
{
public:
    LobbyScene(sf::RenderWindow* rw, SceneManager* sm);
    ~LobbyScene();

    void update(const float dt)override;
    void draw(sf::RenderTarget* rt)override;
    void playerList();
	void readyCheck();
    void ready();
	void disconnect();
	

private:
    GUIArea m_gui;
	sf::Texture readyUp;
	sf::Texture readyDown;
	sf::Texture readyHover;
	sf::Texture discUp;
	sf::Texture discDown;
	sf::Texture discHover;
	float m_total_time;
	bool isReady = false;
	
};

#endif