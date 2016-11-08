#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML\Graphics.hpp>
//#include "UudistusMath.h"
//#include "Component.h"

class Scene;
class Component;

class GameObject
{
public:
    GameObject(const int ID, const sf::Vector2f position, float size, const int owner, const std::string type, sf::Texture* texture = nullptr, const float energy = 0);

    //virtual void update(const float dt) = 0;
    //virtual void render(sf::RenderTarget* rt) = 0;

    void update(const float dt);
    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    void setSize(float size);
    void setEnergy(float energy);
    void setOwner(int owner);

    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    float getSize();
    float getEnergy();
    int getOwner();
    std::string getType();

    float getDistanceToPoint(sf::Vector2f point);
    //float getDistanceToPoint(ud::Vec2 point);
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
    sf::Vector2f m_position;
    std::string m_type; //Enum?
    float m_energy;
    float m_size;
    int m_owner;
    int m_ID;
    //int m_team;

    std::vector<Component*> m_components;

    Scene* m_scene;
};

#endif