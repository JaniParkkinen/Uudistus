#pragma once

#include "GameObject.h"

class Structure : public GameObject
{
public:
    Structure(const float x, const float y, const sf::Sprite* = nullptr);
    void update(const float dt)override;
private:

};