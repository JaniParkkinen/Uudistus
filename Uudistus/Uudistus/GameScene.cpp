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
        go->getSprite()->setPosition(go->getPosition());
    }
}

void GameScene::render(sf::RenderTarget* rt)
{
    //rt->draw(sf::Sprite(tex));
    sf::RectangleShape line(sf::Vector2f(100, 5));
    line.setFillColor(sf::Color::Cyan);

    for (GameObject* go : m_world)
    {
        rt->draw(*go->getSprite());
    }

    //draw connections
    for (Star* star : m_stars)
    {
        for (Connection c : star->m_connections)
        {
            sf::Vector2f total = star->getPosition() + c.target->getPosition();
            sf::Vector2f center(total.x / 2, total.y / 2);

            line.setPosition(center);
            line.setRotation(atan2(total.y, total.x));

            rt->draw(line);
        }
    }
}

void GameScene::generateLevel()
{
    createStar(sf::Vector2f(64, 64), 0, 500);
    createStar(sf::Vector2f(400, 64), 1, 400);
    createStar(sf::Vector2f(400, 400), 2, 300);
    createStar(sf::Vector2f(128, 32), 2, 300);

    m_stars[0]->connect(m_stars[1]);
}

bool GameScene::createStar(sf::Vector2f position, int owner, float energy)
{
    for (Star* star : m_stars)
    {
        if (star->getDistanceToPoint(position) < 256.0f)
            return false;
    }
    Star* newStar = new Star(position, owner, &tex, energy);

    m_world.push_back(newStar);
    m_stars.push_back(newStar);

    return true;
}