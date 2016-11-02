#pragma once

#include <SFML\Graphics.hpp>

class Scene;

class GameObject
{
public:
    GameObject(const sf::Vector2f position, const int owner, const std::string type, sf::Texture* texture = nullptr, const float energy = 0);

    //virtual void update(const float dt) = 0;
    //virtual void render(sf::RenderTarget* rt) = 0;

    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();

    float getDistanceToPoint(sf::Vector2f point);
    float getDistanceToPoint(float x, float y);

protected:
    sf::Sprite* m_sprite;
    sf::Vector2f m_position;
    std::string m_type; //Enum?
    float m_energy;
    int m_owner;
    //int m_team;

    Scene* m_scene;
};