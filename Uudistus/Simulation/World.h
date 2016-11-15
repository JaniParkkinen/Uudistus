#ifndef WORLD_H
#define WORLD_H

#include "GameObject.h"
#include "Star.h"
#include "Ship.h"

#include <vector>

class World
{
public:
    World();
    void update(float dt);
    void createStar(const float x, const float y, const int owner, const float energy = 0);
    void createShip(const float x, const float y, const int owner, const float energy, GameObject* target, float speed);
    //void sendShip(const Star* sender, const Star* target);
    void connectStars(const Star* star1, const Star* star2);
    void generateMap(int seed);

    const std::vector<GameObject*>& getObjects();
    const std::vector<Star*>& getStars();
    const std::vector<Ship*>& getShips();

private:
    int m_ID;

    //GameObject* findObject(int ID);

    std::vector<GameObject*> m_objects;
    std::vector<Star*> m_stars;
    std::vector<Ship*> m_ships;
};

#endif
