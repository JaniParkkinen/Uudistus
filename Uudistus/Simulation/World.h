#ifndef WORLD_H
#define WORLD_H

#include "GameObject.h"
#include "Star.h"
#include "Ship.h"

#include <vector>
#include <mutex>

class World
{
public:
    World();
    void update(float dt);
    void createStar(const float x, const float y, const int owner, const float energy = 0);
    void createShip(const float x, const float y, const int owner, const float energy, GameObject* target, float speed);
    void sendShip(const int sender, const int target);
    void connectStars(const int star1, const int star2);
    void generateMap(int seed);

    const std::vector<GameObject*>& getObjects();
    const std::vector<Star*>& getStars();
    const std::vector<Ship*>& getShips();

    std::mutex m_starLock;
    std::mutex m_shipLock;
    //stationLock...
    //otherLock?

    //use events instead of callbaks?
private:
    int m_ID;

    //GameObject* findObject(int ID);

    std::vector<GameObject*> m_objects;
    std::vector<Star*> m_stars;
    std::vector<Ship*> m_ships;

};

#endif
