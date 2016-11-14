#ifndef WORLD_H
#define WORLD_H

#include <vector>

class World
{
public:
    World();
    void update(float dt);
    void createStar(const float x, const float y, const int owner, const float energy = 0);
    void sendShip(const int senderID, const int targetID);
    void connectStars(const int ID1, const int ID2);
private:
    std::vector<GameObject*> m_objects;
    std::vector<Star*> m_stars;
    std::vector<Ship*> m_ships;
};

#endif
