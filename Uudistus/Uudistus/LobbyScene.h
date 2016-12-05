#ifndef LOBBY_SCENE_H
#define LOBBY_SCENE_H

#include "Scene.h"
#include "GuiArea.h"

class LobbyScene : public Scene
{
public:
    LobbyScene(sf::RenderWindow* rw);
    ~LobbyScene();

    void update(const float dt)override;
    void draw(sf::RenderTarget* rt)override;
    void playerList();
    void ready();

private:
    GUIArea m_gui;
};

#endif