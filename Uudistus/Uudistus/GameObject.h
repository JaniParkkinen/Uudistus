#pragma once

#include <SFML\Graphics.hpp>

class GameObject
{
public:
    GameObject(const float x, const float y, sf::Texture* texture = nullptr);

    virtual void update(const float dt) = 0;
    virtual void render(sf::RenderTarget* rt) = 0;

    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();

protected:
    float x, y;
    sf::Sprite* sprite;
    std::string m_name;
    //std::unordered_map<string(or property enum?), int>() properties;

    Scene* m_scene;
};