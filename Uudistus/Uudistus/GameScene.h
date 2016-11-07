#pragma once

#include "Star.h"
#include "Scene.h"

class GameScene : public Scene
{
public:
    GameScene(sf::RenderWindow* window);
    void update(const float dt)override;
    void render(sf::RenderTarget* rt)override;
private:
    sf::Texture tex; //temp default texture
    sf::RenderWindow* window;

    void generateLevel();

    bool createStar(sf::Vector2f position, int owner, float energy = 100);

    sf::Sprite* m_GUIBackground;
    //std::vector<Button*> m_menu;
    std::vector<GameObject*> m_world;
    std::vector<Star*> m_stars;
    //std::vector<GameObject*> m_stars;
    std::vector<GameObject*> m_selected;
    //std::vector<Ship*> m_ships;

    float m_total_time;

    int m_starID = 0;
public: 

};