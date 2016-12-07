#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include <World.h>
#include <vector>
#include "NetworkManager.h"
#include "GuiArea.h"
//#include "Star.h"
//#include "Ship.h"
//#include "GameObject.h"

enum EMode
{
    EModeDefault,
    EModeMenu,
    EModeConnect,
    EModeStation,
};

class GameObject;

class GameScene : public Scene
{
public:
    GameScene(sf::RenderWindow* window, SceneManager* sm);
    ~GameScene();
    void update(const float dt)override;
    void draw(sf::RenderTarget* rt)override;

    void temp();
private:
    sf::Texture tex; //temp default texture
    sf::Texture shipTexture; //temp ship texture
    sf::Texture guiTex; //GUI bg

    sf::Texture buttonUp;
    sf::Texture buttonDown;
    sf::Texture buttonHover;

    sf::Sprite m_starSprite;
    sf::Sprite m_shipSprite;

    sf::Font m_font;

    t_function* m_callbackLambda;

    GUIArea m_gui;
    World m_world;
    NetworkManager m_net;

    EMode m_mode;
    std::vector<GameObject*> m_selected;

    float m_total_time;
    int m_ID = 0;

    //TODO: make this global?
    const sf::Color m_playerColor[10]
    {
        sf::Color(0, 255, 0), //player0
        sf::Color(0, 0, 255),
        sf::Color(255, 0, 0),
        sf::Color(0, 255, 255),
        sf::Color(255, 0, 255),
        sf::Color(255, 255, 0),
        sf::Color(255, 127, 0),
        sf::Color(127, 127, 0),
        sf::Color(255, 255, 255), //unoccupied
        sf::Color(32, 32, 32), //unknown
    };

    bool m_temp;
};

#endif