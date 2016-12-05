#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
    Component() {};
    virtual void update(const float dt)=0;

    GameObject* getGameObject();
    const GameObject* getGameObjectConst()const;

protected:
    GameObject* m_gameObject;
};

#endif