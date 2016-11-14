#include "World.h"

World::World()
{
    printf_s("World construction\n");
}

//### GET ###

const std::vector<GameObject*>& World::getObjects()
{
    return m_objects;
}

const std::vector<Star*>& World::getStars()
{
    return m_stars;
}


//### other ###

void World::createStar(const float x, const float y, const int owner, const float energy)
{
    //create GameObject
    GameObject* go = new GameObject(m_ID++, x, y, 64, owner, "star", energy);

    for (Star* star : m_stars)
    {
        if (star->getGameObject()->getDistanceToPoint(x, y) < 64.0f)
            return;
    }
    Star* newStar = new Star(go, energy);
    go->addComponent(newStar);

    m_objects.push_back(go);
    m_stars.push_back(newStar);
}


void World::createShip(const float x, const float y, int owner, float energy, GameObject* target, float speed)
{
    GameObject* go = new GameObject(m_ID++, x, y, 32.f, owner, "ship", energy);

    Ship* newShip = new Ship(go, target, speed);
    go->addComponent(newShip);

    m_objects.push_back(go);
    m_ships.push_back(newShip);
}

void World::connectStars(const Star* star1, const Star* star2)
{
    for (Star* star : m_stars)
    {
        if (star == star1)
        {
            star->connect(star2);
        }
        if (star == star2)
        {
            star->connect(star1);
        }
    }
}

void World::generateMap(int seed)
{
    //createShip();
}