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

const std::vector<Ship*>& World::getShips()
{
    return m_ships;
}


//### other ###

void World::update(const float dt)
{
    //const std::vector<GameObject*>& objects = getObjects();
    for (unsigned i = 0; i < m_objects.size(); i++)
    {
        if (m_objects[i] != nullptr)
            m_objects[i]->update(dt);
    }

    //destroy all destroyed game objects
    for (unsigned int i = 0; i < m_objects.size(); i++)
    {
        if (m_objects[i]->isDestroyed())
        {
            switch (m_objects[i]->getType())
            {
            case EStar:
                for (unsigned j = 0; j < m_stars.size(); j++)
                {
                    if (static_cast<Star*>(m_objects[i]->getComponent()) == m_stars[j])
                    {
                        for (unsigned k = j; k < m_stars.size() - 1; k++)
                        {
                            m_stars[k] = m_stars[k + 1];
                        }
                        m_stars.pop_back();
                    }
                }
                break;
            case EShip:
                for (unsigned j = 0; j < m_ships.size(); j++)
                {
                    if (static_cast<Ship*>(m_objects[i]->getComponent()) == m_ships[j])
                    {
                        for (unsigned k = j; k < m_ships.size() - 1; k++)
                        {
                            m_ships[k] = m_ships[k + 1];
                        }
                        m_ships.pop_back();
                    }
                }
                break;
            default:
                break;
            }

            delete m_objects[i];
            m_objects[i] = nullptr;

            //move other objects
            for (unsigned int j = i; j < m_objects.size() - 1; j++)
            {
                m_objects[j] = m_objects[j + 1];
            }
            m_objects.pop_back();
        }
    }
}

void World::createStar(const float x, const float y, const int owner, const float energy)
{
    //create GameObject
    GameObject* go = new GameObject(m_ID++, x, y, 64, owner, EStar, energy);

    //this will be done elsewhere
    //for (Star* star : m_stars)
    //{
    //    if (star->getGameObject()->getDistanceToPoint(x, y) < 64.0f)
    //        return;
    //}
    Star* newStar = new Star(go, energy);
    go->addComponent(newStar);

    m_objects.push_back(go);
    m_stars.push_back(newStar);
}


void World::createShip(const float x, const float y, int owner, float energy, GameObject* target, float speed)
{
    GameObject* go = new GameObject(m_ID++, x, y, 32.f, owner, EShip, energy);

    Ship* newShip = new Ship(go, target, speed);
    go->addComponent(newShip);

    m_objects.push_back(go);
    m_ships.push_back(newShip);
}

void World::sendShip(const int sender, const int target)
{
    Star* star1 = nullptr;
    Star* star2 = nullptr;
    for (int i = 0; i < m_stars.size(); i++)
    {
        if (m_stars[i]->getGameObject()->getID() == sender )
        {
            star1 = m_stars[i];
        }
        if (m_stars[i]->getGameObject()->getID() == target)
        {
            star2 = m_stars[i];
        }
    }

    GameObject* go;
    
    go = star1->getGameObject();
    createShip(go->getX(), go->getY(), go->getOwner(), go->getEnergy(), star2->getGameObject(), 10);

}

void World::connectStars(const int id1, const int id2)
{
    Star* star1 = nullptr;
    Star* star2 = nullptr;
    for (int i = 0; i < m_stars.size(); i++)
    {
        if (m_stars[i]->getGameObject()->getID() == id1)
        {
            star1 = m_stars[i];
        }
        if (m_stars[i]->getGameObject()->getID() == id2)
        {
            star2 = m_stars[i];
        }
    }

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
    createStar(64, 64, 1, 9001);
    createStar(256, 64, 2, 9001);
    createStar(64, 256, 3, 9001);

    connectStars(m_stars[0]->getGameObject()->getID(), m_stars[1]->getGameObject()->getID());
}