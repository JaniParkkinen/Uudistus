#include "GameScene.h"

#include "Star.h"
#include "Ship.h"
#include <GameObject.h>

#define PI 3.14159265

GameScene::GameScene(sf::RenderWindow* window)
    :Scene(window),
    m_net(&m_world, "127.0.0.1")
{
    //m_net.createStar(64, 64, 128, 1, 5);
    //m_net.createStar(64, 128, 128, 2, 5);
    //m_net.createStar(128, 64, 128, 3, 5);
    //m_net.createStar(128, 128, 128, 4, 5);

    tex.loadFromFile("assets/star.png");
    shipTexture.loadFromFile("assets/ship.png");

    m_starSprite = sf::Sprite(tex);
    m_shipSprite = sf::Sprite(shipTexture);

    float scale = 64.f / tex.getSize().x;
    m_starSprite.setScale(scale, scale);
    m_starSprite.setOrigin(tex.getSize().x / 2.0f, tex.getSize().y / 2.0f);

    scale = 32.f / shipTexture.getSize().x;
    m_shipSprite.setScale(scale, scale);
    m_shipSprite.setOrigin(shipTexture.getSize().x / 2.0f, shipTexture.getSize().y / 2.0f);

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
    if (m_input->mousePressed(MouseButton::Left)) //single click, select single object
    {
        m_selected.clear();
        for (GameObject* go : objects)
        {
            if (go->getDistanceToPoint(m_input->getMousePos().x, m_input->getMousePos().y) < go->getSize())
            {
                m_selected.push_back(go);
                break;
            }
        }
    }
    if (m_input->mousePressed(MouseButton::Right))
    {
        for (GameObject* go : objects)
        {
            if (go->getType() == EStar)
            {
                if (go->getDistanceToPoint(m_input->getMousePos().x, m_input->getMousePos().y) < go->getSize())
                {
                    for (GameObject* selected : m_selected)
                    {
                        if (selected->getType() == EStar)
                        {
                            m_world.createShip(selected->getX(), selected->getY(), selected->getOwner(), selected->getEnergy(), go, 10.0f);
                            m_net.createStar(m_input->getMousePos().x, m_input->getMousePos().y, 128, 4, 5);
                        }
                    }
                    break;
                }
            }
        }
    }
    m_world.update(dt);
    //TODO: remove deleted objects from m_selected


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

    //draw stars and connections
    for (Star* star : m_world.getStars())
    {
        //draw star
        m_starSprite.setPosition(star->getGameObject()->getX(), star->getGameObject()->getY());
        rt->draw(m_starSprite);

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

    //draw ships
    //for (Ship* ship : m_world.getShips())
    const std::vector<Ship*> ships = m_world.getShips();
    for(int i = 0; i < ships.size(); i++)
    {
        Ship* ship = ships[i];
        m_shipSprite.setRotation(ship->getDirection() * 180.f / 3.14159265f);

        m_shipSprite.setPosition(ship->getGameObject()->getX(), ship->getGameObject()->getY());
        rt->draw(m_shipSprite);
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