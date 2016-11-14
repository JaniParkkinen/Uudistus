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

    int seed = 0;
    //get seed from server

    m_world.generateMap(seed);
}

void GameScene::update(float dt)
{
    const std::vector<GameObject*>& objects = m_world.getObjects();

    if (m_rw != nullptr)
        m_input->update(dt, m_rw);

    m_total_time += dt;

    for (GameObject* go : objects)
    {
        go->update(dt);
    }

    //selection
    if (m_input->mousePressed(MouseButton::Left))
    {
        m_selected.clear();
        for (GameObject* go : objects)
        {
            if (go->getDistanceToPoint(m_input->getMousePos().x, m_input->getMousePos().y) < go->getSize())
            {
                m_selected.push_back(go);
            }
        }
    }
    if (m_input->mousePressed(MouseButton::Right))
    {
        for (GameObject* go : objects)
        {
            if (go->getDistanceToPoint(m_input->getMousePos().x, m_input->getMousePos().y) < go->getSize())
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

    for (GameObject* go : m_world.getObjects())
    {
        //TODO switch case
    }

    //draw connections
    for (Star* star : m_world.getStars())
    {
        for (Connection* c : star->getConnections())
        {
            GameObject* starObject = star->getGameObject();
            const GameObject* targetObject = c->target->getGameObjectConst();
            if (starObject->getID() < targetObject->getID())
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(starObject->getX(), starObject->getY())),
                    sf::Vertex(sf::Vector2f(targetObject->getX(), targetObject->getY()))
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
        selection.setPosition(sf::Vector2f(go->getX(), go->getY()));
        rt->draw(selection);
    }
}