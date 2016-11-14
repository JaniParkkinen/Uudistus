#include "Component.h"
#include "GameObject.h"

GameObject* Component::getGameObject()
{
    return m_gameObject;
}