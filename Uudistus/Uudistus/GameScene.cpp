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
    m_gui(600, 0, 200, 200, 4, 1),
    m_buttons(600, 200, 200, 600, 12, 2),
    m_view(sf::Vector2f(400, 400), sf::Vector2f(800, 800))
{
    NetworkManager::instance()->setWorld(&m_world);

    tex.loadFromFile("assets/star.png");
    shipTexture.loadFromFile("assets/ship.png");
    guiTex.loadFromFile("assets/gui.png");

    connectUp.loadFromFile("assets/connect_up.png");
    connectDown.loadFromFile("assets/connect_down.png");
    connectHover.loadFromFile("assets/connect_hover.png");

    upgradeUp.loadFromFile("assets/upgrade_up.png");
    upgradeDown.loadFromFile("assets/upgrade_down.png");
    upgradeHover.loadFromFile("assets/upgrade_hover.png");

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
    m_tickTime = 0;
    m_average_tick = 10.f / 60.f;

    m_rw = window;
	m_sm = sm;

    int seed = 0;
    //TODO: get seed from server

    m_world.generateMap(NetworkManager::g_nPlayers);

    m_world.m_starLock.lock();
    for (const Star* star : m_world.getStars())
    {
        if (star->getGameObjectConst()->getOwner() == NetworkManager::g_playerNumber)
        {
            m_view.setCenter(star->getGameObjectConst()->getX(), star->getGameObjectConst()->getY());
        }
    }
    m_world.m_starLock.unlock();

    m_buttons.setBackground(&guiTex);
    m_buttons.setBorder(32, 32);
    m_buttons.setElementMargin(8, 8);

    m_gui.setBackground(&guiTex);
    m_gui.setBorder(32, 32);
    m_gui.setElementMargin(8, 8);

    m_gui.createText("Energy", "---", &m_font);
    m_gui.createText("Owner", "---", &m_font);
    m_gui.createText("Level", "", &m_font);
}

GameScene::~GameScene()
{
    delete m_callbackLambda;
}

void GameScene::upgradeStar()
{
    static_cast<Star*>(m_selected[0]->getComponent())->upgrade();
}

void GameScene::modeConnect()
{
    m_mode = EMode::EModeConnect;
}

void GameScene::temp()
{
    printf_s("Temp called!\n");
    for (int i = 0; i < 20; i++)
    {
        NetworkManager::instance()->sendShip(0, 1);
    }
}

void GameScene::update(float dt)
{
    m_gui.update();
    m_buttons.update();

    if (m_selected.size() > 0)
    {
        m_gui.getElementByName<GUIText>("Energy")->setText("E:" + std::to_string(m_selected[0]->getEnergy()));
        if (m_selected[0]->getOwner() == 0)
        {
            m_gui.getElementByName<GUIText>("Owner")->setText("Unoccupied");
        }
        else
        {
            m_gui.getElementByName<GUIText>("Owner")->setText("Player " + std::to_string(m_selected[0]->getOwner()));
        }
        if (m_selected[0]->getType() == EStar)
        {
            m_gui.getElementByName<GUIText>("Level")->setText("Level: " + std::to_string(static_cast<Star*>(m_selected[0]->getComponent())->getLevel()));
        }
    }

    //if (m_input->mousePressed(MouseButton::Left))
    //{
    //    sf::Vector2f mPos = m_input->getMousePos();
    //    printf_s("mouse position: %f, %f\n", mPos.x, mPos.y);
    //}

    if (m_rw != nullptr)
        m_input->update(dt, m_rw);

    m_total_time += dt;
    m_tickTime += dt;
    if (NetworkManager::instance()->getTick() > m_tick)
    {
        m_average_tick = (m_average_tick * 0.75f + m_tickTime * 0.25f);
        m_tickTime = dt;
        m_tick = NetworkManager::instance()->getTick();
    }

    const std::vector<GameObject*>& objects = m_world.getObjects();

    //change mode
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        if (m_selected.size() == 1 && m_selected[0]->getType() == EStar && m_selected[0]->getOwner() == NetworkManager::g_playerNumber)
        {
            m_mode = EModeConnect;
        }
    }

    //Mouse interaction
    sf::Vector2f mousePos = m_input->getMousePos();
    if (m_input->getMousePosWindow().x < 600)
    {

        //default mode
        if (m_mode == EModeDefault)
        {
            if (m_input->mousePressed(MouseButton::Left)) //single click, select single object
            {
                ObjectType oldType = ObjectType::EOther;
                int oldPlayer = -1;
                if (m_selected.size() != 0)
                {
                    oldType = m_selected[0]->getType();
                    oldPlayer = m_selected[0]->getOwner();
                }

                m_selected.clear();
                m_world.m_shipLock.lock();
                m_world.m_starLock.lock();
                for (GameObject* go : objects)
                {
                    if (go->getDistanceToPoint(mousePos.x, mousePos.y) < go->getSize() / 2.f)
                    {
                        m_selected.push_back(go);
                        if (m_selected[0]->getOwner() != oldPlayer || m_selected[0]->getType() != oldType/* || m_selected[0]->getOwner() == NetworkManager::g_playerNumber*/)
                        {
                            m_buttons.clearButtons();
                            if (go->getType() == EStar)
                            {
                                if (m_selected[0]->getOwner() == NetworkManager::g_playerNumber)
                                {
                                    m_buttons.createButton("star_connect", std::bind(&GameScene::modeConnect, this), &connectUp, &connectDown, &connectHover);
                                    m_buttons.createButton("star_upgrade", std::bind(&GameScene::upgradeStar, this), &upgradeUp, &upgradeDown, &upgradeHover);
                                }
                            }
                        }
                        break;
                    }
                }
                if (m_selected.size() == 0)
                {
                    m_buttons.clearButtons();
                }
                m_gui.getElementByName<GUIText>("Energy")->setText("Nothing");
                m_gui.getElementByName<GUIText>("Owner")->setText("Selected");
                m_gui.getElementByName<GUIText>("Level")->setText("");
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
                        if (go->getDistanceToPoint(mousePos.x, mousePos.y) < go->getSize() / 2.f)
                        {
                            for (GameObject* selected : m_selected)
                            {
                                if (selected->getType() == EStar && selected->getOwner() == NetworkManager::g_playerNumber)
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
                        if (go->getDistanceToPoint(mousePos.x, mousePos.y) < go->getSize() / 2.f)
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
    }
    
    for (int i = 0; i < m_selected.size(); i++)
    {
        if (m_selected[i]->isDestroyed())
        {
            for (int j = i; j < m_selected.size() - 1; j++)
            {
                m_selected[j] = m_selected[j + 1];
            }
            m_selected.pop_back();
            m_buttons.clearButtons();

            m_gui.getElementByName<GUIText>("Energy")->setText("Nothing");
            m_gui.getElementByName<GUIText>("Owner")->setText("Selected");
        }
    }
}

void GameScene::draw(sf::RenderTarget* rt)
{
    //special modes
    if (m_mode == EModeConnect)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(m_selected[0]->getX(), m_selected[0]->getY())),
            sf::Vertex(InputManager::instance()->getMousePos())
        };
        line[0].color = m_playerColor[m_selected[0]->getOwner()];
        line[1].color = sf::Color::White;
        rt->draw(line, 2, sf::Lines);
    }

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
                rt->draw(line, 2, sf::Lines);
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

        Vec2 pos = interpolateToDirection(ship->getGameObject()->getX(), ship->getGameObject()->getY(), ship->getDirection(), ship->getSpeed());

        m_shipSprite.setPosition(pos.x, pos.y);
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
        float radius = go->getSize() / 2.0f + 4.f;
        selection.setRadius(radius);
        selection.setOrigin(radius, radius);
        selection.setPosition(sf::Vector2f(go->getX(), go->getY()));
        rt->draw(selection);
    }

    //draw GUI
    m_gui.draw(rt);
    m_buttons.draw(rt);
    updateView(rt);
    rt->setView(m_view);
}

Vec2 GameScene::interpolate(float x1, float y1, float x2, float y2)
{
    float scale = m_tickTime / m_average_tick;
    float x = x1 + ((x2 - x1) * scale);
    float y = y1 + ((y2 - y1) * scale);

    return Vec2(x, y);
}

Vec2 GameScene::interpolateToDirection(float x1, float y1, float direction, float speed)
{
    float units_per_tick = speed * 0.1f; //0.1 = simulation tick time

    Vec2 result = interpolate(x1, y1, x1 +cos(direction) * units_per_tick, y1 + sin(direction) * units_per_tick);

    return result;
}

void GameScene::updateView(sf::RenderTarget* rt)
{
    sf::Vector2i pos = m_input->getMousePosWindow(); //GUI coordinates

    rt->setView(m_view);
    if (pos.x < 32)
    {
        m_view.move(-1.f, 0);
    }
    else if (pos.x > rt->getSize().x - 32)
    {
        m_view.move(1.f, 0);
    }
    if (pos.y < 32)
    {
        m_view.move(0, -1.f);
    }
    else if (pos.y > rt->getSize().y - 32)
    {
        m_view.move(0, 1.f);
    }
}