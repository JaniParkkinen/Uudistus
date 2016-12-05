#include "Component.h"
#include "GameObject.h"

GameObject* Component::getGameObject()
{
    return m_gameObject;
}

const GameObject* Component::getGameObjectConst()const
{
    return m_gameObject;
}