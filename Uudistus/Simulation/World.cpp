#include "World.h"

World::World()
    :m_ships(),
    m_stars(),
    m_objects()
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
    for (unsigned i = 0; i < m_objects.size(); i++)
    {
        if (m_objects[i] != nullptr)
            m_objects[i]->update(dt);
    }

    //ship-ship collisions
    //TODO: move to ship
    for (int i = 0; i < static_cast<int>(m_ships.size()) - 1; i++)
    {
        for (unsigned j = i+1; j < m_ships.size(); j++)
        {
            GameObject* ship1 = m_ships[i]->getGameObject();
            GameObject* ship2 = m_ships[j]->getGameObject();
            if (ship1->getOwner() != ship2->getOwner())
            {
                float dx = ship1->getX() - ship2->getX();
                float dy = ship1->getY() - ship2->getY();
                float distance2 = dx*dx + dy*dy;

                if (distance2 < 32 * 32)
                {
                    if (ship1->getEnergy() < ship2->getEnergy())
                    {
                        ship2->setEnergy(ship2->getEnergy() - ship1->getEnergy());
                        ship1->destroy();
                    }
                    else
                    {
                        ship1->setEnergy(ship1->getEnergy() - ship2->getEnergy());
                        ship2->destroy();
                    }
                }
            }
        }
    }

    //destroy all destroyed game objects
    for (unsigned int i = 0; i < m_objects.size(); i++)
    {
        if (m_objects[i]->isDestroyed())
        {
            switch (m_objects[i]->getType())
            {
            case EStar:
                m_starLock.lock();
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
                m_starLock.unlock();
                break;
            case EShip:
                m_shipLock.lock();
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
                m_shipLock.unlock();
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
    GameObject* go = new GameObject(m_ID++, x, y, 64.f, owner, EStar, energy);

    //this will be done elsewhere
    //for (Star* star : m_stars)
    //{
    //    if (star->getGameObject()->getDistanceToPoint(x, y) < 64.0f)
    //        return;
    //}
    Star* newStar = new Star(go, energy);
    go->addComponent(newStar);

    m_starLock.lock();
    m_objects.push_back(go);
    m_stars.push_back(newStar);
    m_starLock.unlock();
}


void World::createShip(const float x, const float y, int owner, float energy, GameObject* target, float speed)
{
    GameObject* go = new GameObject(m_ID++, x, y, 32.f, owner, EShip, energy);

    Ship* newShip = new Ship(go, target, speed);
    go->addComponent(newShip);

    m_shipLock.lock();
    m_objects.push_back(go);
    m_ships.push_back(newShip);
    m_shipLock.unlock();
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

    float speed = 10;
    for (Connection* c : star1->getConnections())
    {
        if (c->target == star2)
        {
            speed = 20;
        }
    }

    GameObject* go;
    
    go = star1->getGameObject();
    createShip(go->getX(), go->getY(), go->getOwner(), go->getEnergy(), star2->getGameObject(), speed);
    go->setEnergy(0.f);

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

void World::generateMap(int nPlayers)
{
    m_nPlayers = nPlayers;

    createStar(0, 0, 0, 100);

    srand(nPlayers);

    const float sector = 3.14159265 * 2 / nPlayers;

    for (int i = 0; i < 5; i++)
    {
        float x;
        float y;
        float d;
        do
        {
            x = rand() % 500;
            y = rand() % 500;
            //find closest star
            d = FLT_MAX;
            for (Star* star : m_stars)
            {
                float dx = star->getGameObject()->getX() - x;
                float dy = star->getGameObject()->getY() - y;
                float d2 = dx*dx + dy*dy;
                if (d2 < d)
                {
                    d = d2;
                }
            }
        }while (d < 64*64);

        const float dist = sqrt(x*x + y*y);
        const float dir = atan2(y, x);

        for (int j = 0; j < nPlayers; j++)
        {
            createStar(cos(sector * j + dir) * dist, sin(sector * j + dir) * dist, i == 4 ? j + 1 : 0, j == 4 ? 250 : 100);
        }
    }
}