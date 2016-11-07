#pragma once

#include <SFML\Graphics.hpp>
#include "Component.h"

class Scene;

class GameObject
{
public:
    GameObject(const int ID, const ud::Vec2 position, const int owner, const std::string type, sf::Texture* texture = nullptr, const float energy = 0);

    //virtual void update(const float dt) = 0;
    //virtual void render(sf::RenderTarget* rt) = 0;

    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    ud::Vec2 getPosition();
    sf::Sprite* getSprite();

    float getDistanceToPoint(sf::Vector2f point);
    float getDistanceToPoint(ud::Vec2 point);
    float getDistanceToPoint(float x, float y);
    int getID();

    void addComponent(Component* cmp)
    {
        m_components.push_back(cmp);
    }

    Scene* getScene() { return m_scene; }

    template<typename ComponentType>
    ComponentType* GetComponent() {
        for (unsigned int i = 0; i < m_components.size(); i++) {
            if (ComponentType* cmp = dynamic_cast<ComponentType*>(m_components[i])) {
                return cmp;
            }
        }
        return NULL;
    }

protected:
    sf::Sprite* m_sprite;
    ud::Vec2 m_position;
    std::string m_type; //Enum?
    float m_energy;
    int m_owner;
    int m_ID;
    //int m_team;

    std::vector<Component*> m_components;

    Scene* m_scene;
};