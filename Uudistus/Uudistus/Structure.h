#pragma once

#include "GameObject.h"

class Scene;

class Structure : public GameObject
{
public:
    Structure(const float x, const float y, Scene* scene, sf::Texture* tex = nullptr);
    void update(const float dt)override;
    void render(sf::RenderTarget* rt)override;
private:
    float m_size;
    Scene* m_scene;
};