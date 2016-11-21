#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include <World.h>
#include <vector>
#include "NetworkManager.h"
//#include "Star.h"
//#include "Ship.h"
//#include "GameObject.h"

class GameObject;

class GameScene : public Scene
{
public:
    GameScene(sf::RenderWindow* window);
    void update(const float dt)override;
    void render(sf::RenderTarget* rt)override;
private:
    sf::Texture tex; //temp default texture
    sf::Texture shipTexture; //temp ship texture

    sf::Sprite m_starSprite;
    sf::Sprite m_shipSprite;

    World m_world;

    sf::Sprite* m_GUIBackground;
    //std::vector<Button*> m_menu;

    std::vector<GameObject*> m_selected;

    NetworkManager m_net;
    
    float m_total_time;

    int m_ID = 0;
public: 

};

#endif