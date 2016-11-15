#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//#include <SFML\Graphics.hpp>
#include "Component.h"
#include <vector>
class Scene;
//class Component;

enum ObjectType
{
    EStar,
    EShip,
};

class GameObject
{
public:
    GameObject(const int ID, const float x, const float y, float size, const int owner, const ObjectType type, const float energy = 0);
    ~GameObject();

    void update(const float dt);
    void setPosition(float x, float y);
    void setSize(float size);
    void setEnergy(float energy);
    void setOwner(int owner);

    const float getX()const;
    const float getY()const;
    float getSize();
    float getEnergy();
    int getOwner();
    ObjectType getType();

    float getDistanceToPoint(float x, float y);
    const int getID()const;

    void addComponent(Component* cmp)
    {
        m_components.push_back(cmp);
    }

    Scene* getScene() { return m_scene; }

    //template<typename ComponentType>
    //ComponentType* GetComponent() {
    //    for (unsigned int i = 0; i < m_components.size(); i++) {
    //        if (ComponentType* cmp = dynamic_cast<ComponentType*>(m_components[i])) {
    //            return cmp;
    //        }
    //    }
    //    return NULL;
    //}

    Component* getComponent();

    void destroy();
    bool isDestroyed();

protected:
    float m_x, m_y;
    ObjectType m_type;
    float m_energy;
    float m_size;
    int m_owner;
    int m_ID;
    bool m_isDestroyed;
    //int m_team;

    std::vector<Component*> m_components;

    Scene* m_scene;
};

#endif