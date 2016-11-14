#include "GameScene.h"

#include "Star.h"
#include "Ship.h"
#include <GameObject.h>

#define PI 3.14159265

GameScene::GameScene(sf::RenderWindow* window)
    :Scene(window)
{
    tex.loadFromFile("assets/star.png");
    shipTexture.loadFromFile("assets/ship.png");

    m_total_time = 0;

    m_rw = window;

    //generateLevel();
}

void GameScene::update(float dt)
{
    if (m_rw != nullptr)
        m_input->update(dt, m_rw);

    m_total_time += dt;

    for (GameObject* go : m_objects)
    {
        go->update(dt);
    }

    //selection
    if (m_input->mousePressed(MouseButton::Left))
    {
        m_selected.clear();
        for (GameObject* go : m_objects)
        {
            if (go->getDistanceToPoint(m_input->getMousePos()) < go->getSize())
            {
                m_selected.push_back(go);
            }
        }
    }
    if (m_input->mousePressed(MouseButton::Right))
    {
        for (GameObject* go : m_objects)
        {
            if (go->getDistanceToPoint(m_input->getMousePos()) < go->getSize())
            {
                for (GameObject* selected : m_selected)
                {
                    if (selected->getType() == "star")
                    {
                        //createShip(selected->getPosition(),selected->getOwner(), selected->getEnergy(), go);
                    }
                }
                break;
            }
        }
    }

    //destroy all destroyed game objects
    //for (unsigned int i = 0; i < m_world.size(); i++)
    //{
    //    if (m_world[i]->isDestroyed())
    //    {
    //        delete m_world[i];
    //        m_world[i] = nullptr;

    //        //move other objects
    //        for (unsigned int j = i; j < m_world.size() - 1; j++)
    //        {
    //            m_world[j] = m_world[j + 1];
    //        }
    //        m_world.pop_back();
    //    }
    //}
}

void GameScene::render(sf::RenderTarget* rt)
{
    ////draw grid
    //sf::RectangleShape square(sf::Vector2f(32, 32));
    //for (int i = 0; i < 32; i++)
    //{
    //    for (int j = 0; j < 32; j++)
    //    {
    //        square.setFillColor(((i+j)%2==0) ? sf::Color::Black : sf::Color::Green);
    //        square.setPosition(i * 32, j * 32);
    //        rt->draw(square);;
    //    }
    //}

    for (GameObject* go : m_world)
    {
        rt->draw(*go->getSprite());
    }

    //draw connections
    for (Star* star : m_stars)
    {
        for (Connection* c : star->getConnections())
        {
            if (star->getGameObject()->getID() < c->target->getGameObject()->getID())
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(star->getGameObject()->getPosition()),
                    sf::Vertex(c->target->getGameObject()->getPosition())
                };
                line[0].color = sf::Color::Cyan;
                line[1].color = sf::Color::Cyan;
                rt->draw(line, 5, sf::Lines);
            }
        }
    }

    //draw selection
    sf::CircleShape selection;
    selection.setFillColor(sf::Color::Transparent);
    selection.setOutlineColor(sf::Color::White);
    selection.setOutlineThickness(2);

    for (GameObject* go : m_selected)
    {
        selection.setRadius(go->getSize() / 2 + 32.f);
        selection.setOrigin(go->getSize(), go->getSize());
        selection.setPosition(go->getPosition());
        rt->draw(selection);
    }
}

void GameScene::generateLevel()
{
    createStar(sf::Vector2f(64, 64), 0, 500);
    createStar(sf::Vector2f(512, 64), 1, 400);

    m_stars[0]->connect(m_stars[1]);
}

bool GameScene::createStar(sf::Vector2f position, int owner, float energy)
{
    //create GameObject
    GameObject* go = new GameObject(m_ID++, position, 64, owner, "star", &tex);

    for (Star* star : m_stars)
    {
        if (star->getGameObject()->getDistanceToPoint(position) < 256.0f)
            return false;
    }
    Star* newStar = new Star(go, energy);
    go->addComponent(newStar);

    m_world.push_back(go);
    m_stars.push_back(newStar);

    return true;
}


bool GameScene::createShip(sf::Vector2f position, int owner, float energy, GameObject* target, float speed)
{
    GameObject* go = new GameObject(m_ID++, position, 32.f, owner, "ship", &shipTexture, energy);

    Ship* newShip = new Ship(go ,target, speed);
    go->addComponent(newShip);

    m_world.push_back(go);
    m_ships.push_back(newShip);

    return true;
}