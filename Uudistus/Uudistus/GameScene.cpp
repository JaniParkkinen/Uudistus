#include "GameScene.h"

GameScene::GameScene(sf::RenderWindow* window)
    :Scene(window), window(window)
{
    tex.loadFromFile("assets/star.png");
    m_total_time = 0;

    generateLevel();
}

void GameScene::update(float dt)
{
    Scene::update(dt);
    m_total_time += dt;
    for (GameObject* go : m_world)
    {
        //go->setPosition((cos(m_total_time) + 1) * 200, (sin(m_total_time) + 1) * 200);
        ud::Vec2 pos = go->getPosition();
        go->getSprite()->setPosition(sf::Vector2f(pos.x, pos.y));
    }
}

void GameScene::render(sf::RenderTarget* rt)
{
    ////rt->draw(sf::Sprite(tex));
    //sf::RectangleShape line(sf::Vector2f(100, 5));
    //line.setFillColor(sf::Color::Cyan);

    //for (GameObject* go : m_world)
    //{
    //    rt->draw(*go->getSprite());
    //}

    ////draw connections
    //for (Star* star : m_stars)
    //{
    //    for (Connection c : star->m_connections)
    //    {
    //        if (star->getID() < c.target->getID())
    //        {
    //            sf::Vector2f total = star->getPosition() + c.target->getPosition();
    //            sf::Vector2f center(total.x / 2, total.y / 2);

    //            line.setSize(sf::Vector2f(c.length, 4));
    //            line.setPosition(center);
    //            line.setRotation(atan2(total.y, total.x));

    //            rt->draw(line);
    //        }
    //    }
    //}
}

void GameScene::generateLevel()
{
    createStar(ud::Vec2(64, 64), 0, 500);
    createStar(ud::Vec2(400, 64), 1, 400);

    m_stars[0]->connect(m_stars[1]);
}

bool GameScene::createStar(ud::Vec2 position, int owner, float energy)
{
    //create GameObject

    GameObject* go = new GameObject(m_starID++, position, owner, "star");

    for (Star* star : m_stars)
    {
        if (star->getGameObject()->getDistanceToPoint(position) < 256.0f)
            return false;
    }
    Star* newStar = new Star(energy);
    go->addComponent(newStar);

    m_world.push_back(go);
    m_stars.push_back(newStar);

    return true;
}