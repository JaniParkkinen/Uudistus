#ifndef SHIP_H
#define SHIP_H

#include "Component.h"

class Ship : public Component
{
public:
    Ship(GameObject* parent, GameObject* target, float speed);

    void update(const float dt)override;

private:
    GameObject* m_target;
    float m_speed;
};

#endif