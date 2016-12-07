#include "GameScene.h"

#include "Star.h"
#include "Ship.h"
#include <GameObject.h>
#include "GuiArea.h"
#include "GUIText.h"

#define PI 3.14159265

GameScene::GameScene(sf::RenderWindow* window, SceneManager* sm)
    :Scene(window, sm),
    m_mode(EModeDefault),
    m_gui(600, 0, 200, 800, 16, 2)

{
    NetworkManager::instance()->setWorld(&m_world);

    tex.loadFromFile("assets/star.png");
    shipTexture.loadFromFile("assets/ship.png");
    guiTex.loadFromFile("assets/gui.png");

    buttonUp.loadFromFile("assets/button_up.png");
    buttonDown.loadFromFile("assets/button_down.png");
    buttonHover.loadFromFile("assets/button_hover.png");

    m_font.loadFromFile("assets/COLONNA.TTF");

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
	m_sm = sm;

    int seed = 0;
    //get seed from server

    m_world.generateMap(seed);

    m_gui.setBackground(&guiTex);
    m_gui.setBorder(32, 32);
    m_gui.setElementMargin(8, 8);

    m_gui.createText("Energy", "---", &m_font);
}

GameScene::~GameScene()
{
    delete m_callbackLambda;
}

void GameScene::temp()
{
    printf_s("Temp called!\n");
    for (int i = 0; i < 100; i++)
    {
        NetworkManager::instance()->sendShip(0, 1);
    }
}

void GameScene::update(float dt)
{
    if (m_selected.size() > 0)
    {
        m_gui.getElementByName<GUIText>("Energy")->setText("E:" + std::to_string(m_selected[0]->getEnergy()));
    }

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
            m_world.m_shipLock.lock();
            m_world.m_starLock.lock();
            for (GameObject* go : objects)
            {
                if (go->getDistanceToPoint(m_input->getMousePos().x, m_input->getMousePos().y) < go->getSize())
                {
                    m_selected.push_back(go);
                    break;
                }
            }
            m_world.m_starLock.unlock();
            m_world.m_shipLock.unlock();
        }
        if (m_input->mousePressed(MouseButton::Right))
        {
            m_world.m_shipLock.lock();
            m_world.m_starLock.lock();
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
                                NetworkManager::instance()->sendShip(selected->getID(), go->getID());
                            }
                        }
                        break;
                    }
                }
            }
            m_world.m_starLock.unlock();
            m_world.m_shipLock.unlock();
        }
    }
    //connect
    else if (m_mode == EModeConnect)
    {
        if (m_input->mousePressed(MouseButton::Left))
        {
            m_world.m_shipLock.lock();
            m_world.m_starLock.lock();
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
								NetworkManager::instance()->connect(selected->getID(), go->getID());
                                m_mode = EModeDefault;
                            }
                        }
                        break;
                    }
                }
            }
            m_world.m_starLock.unlock();
            m_world.m_shipLock.unlock();
        }

        if (m_input->mousePressed(MouseButton::Right))
        {
            m_mode = EModeDefault;
        }
    }
    //TODO: remove deleted objects from m_selected
}

void GameScene::draw(sf::RenderTarget* rt)
{
    //draw stars and connections
    const std::vector<Star*> stars = m_world.getStars();
    m_world.m_starLock.lock();
    for (unsigned i = 0; i < stars.size(); i++)
    {
        Star* star = stars[i];
        //draw star
        m_starSprite.setPosition(star->getGameObject()->getX(), star->getGameObject()->getY());
        m_starSprite.setColor(m_playerColor[stars[i]->getGameObject()->getOwner()]);
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
                line[0].color = m_playerColor[starObject->getOwner()];
                line[1].color = m_playerColor[targetObject->getOwner()];
                rt->draw(line, 5, sf::Lines);
            }
        }
    }
    m_world.m_starLock.unlock();

    m_world.m_shipLock.lock();
    const std::vector<Ship*> ships = m_world.getShips();
    for(unsigned i = 0; i < ships.size(); i++)
    {
        Ship* ship = ships[i];
        m_shipSprite.setRotation(ship->getDirection() * 180.f / 3.14159265f);

        m_shipSprite.setPosition(ship->getGameObject()->getX(), ship->getGameObject()->getY());
        m_shipSprite.setColor(m_playerColor[ship->getGameObject()->getOwner()]);
        rt->draw(m_shipSprite);
    }
    m_world.m_shipLock.unlock();

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