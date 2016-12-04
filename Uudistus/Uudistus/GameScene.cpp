#include "GameScene.h"

#include "Star.h"
#include "Ship.h"
#include <GameObject.h>
#include "GuiArea.h"

#define PI 3.14159265

GameScene::GameScene(sf::RenderWindow* window)
    :Scene(window),
    m_mode(EModeDefault),
    m_net(&m_world, "127.0.0.1"),
    m_gui(600, 0, 200, 800, 16)
{
    tex.loadFromFile("assets/star.png");
    shipTexture.loadFromFile("assets/ship.png");
    guiTex.loadFromFile("assets/gui.png");

    buttonUp.loadFromFile("assets/button_up.png");
    buttonDown.loadFromFile("assets/button_down.png");
    buttonHover.loadFromFile("assets/button_hover.png");

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
    //m_callbackLambda = new t_function(
    //std::function<void(void)> f = std::bind(
    //    ([=] {
    //        printf_s("Test1\n");
    //    }), this);


    m_gui.setBackground(&guiTex);

    m_gui.createButton("Test1", std::bind(&GameScene::temp, this), &buttonUp, &buttonDown, &buttonHover);
    m_gui.createButton("Test2", std::bind(&GameScene::temp, this), &buttonUp, &buttonDown, &buttonHover);
    m_gui.createButton("Test3", std::bind(&GameScene::temp, this), &buttonUp, &buttonDown, &buttonHover);
    m_gui.createButton("Test4", std::bind(&GameScene::temp, this), &buttonUp, &buttonDown, &buttonHover);

    m_gui.removeButton("Test3");
}

GameScene::~GameScene()
{
    delete m_callbackLambda;
}

void GameScene::temp()
{
    printf_s("Temp called!\n");
}

void GameScene::update(float dt)
{
    if (m_input->mousePressed(MouseButton::Left))
    {
        sf::Vector2f mPos = m_input->getMousePos();
        printf_s("mouse position: %f, %f\n", mPos.x, mPos.y);
    }

    if (m_rw != nullptr)
        m_input->update(dt, m_rw);

    m_gui.update();

    m_total_time += dt;

    const std::vector<GameObject*>& objects = m_world.getObjects();
    for (unsigned i = 0; i < objects.size(); i++)
    {
        if (objects[i] != nullptr)
            objects[i]->update(dt);
    }

    //change mode
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        m_mode = EModeConnect;
    }

    //default mode
    if (m_mode == EModeDefault)
    {
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
                                m_net.sendShip(selected->getID(), go->getID());
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    //connect
    else if (m_mode == EModeConnect)
    {
        if (m_input->mousePressed(MouseButton::Left))
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
                                m_net.connect(selected->getID(), go->getID());
                                m_mode = EModeDefault;
                            }
                        }
                        break;
                    }
                }
            }
        }

        if (m_input->mousePressed(MouseButton::Right))
        {
            m_mode = EModeDefault;
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
    const std::vector<Star*> stars = m_world.getStars();
    for (unsigned i = 0; i < stars.size(); i++)
    {
        Star* star = stars[i];
        //draw star
        m_starSprite.setPosition(star->getGameObject()->getX(), star->getGameObject()->getY());
        rt->draw(m_starSprite);

        const std::vector<Connection*> connections = star->getConnections();
        for (unsigned i = 0; i < connections.size(); i++)
        {
            Connection* c = connections[i];
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
    for(unsigned i = 0; i < ships.size(); i++)
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

    for (unsigned i = 0; i < m_selected.size(); i++)
    {
        GameObject* go = m_selected[i];
        selection.setRadius(go->getSize() / 2 + 32.f);
        selection.setOrigin(go->getSize(), go->getSize());
        selection.setPosition(sf::Vector2f(go->getX(), go->getY()));
        rt->draw(selection);
    }

    //draw GUI
    m_gui.draw(rt);
}