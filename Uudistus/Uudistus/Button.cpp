#include "Button.h"

Button::Button(int x, int y, int w, int h, t_function callback, sf::Texture* up, sf::Texture* down, sf::Texture* hover)
{
    m_isActive = true;
    m_callback = callback;

    sf::Sprite* upSprite = new sf::Sprite(*up);
    upSprite->setPosition(x, y);
    float xScale = (float)w / up->getSize().x;
    float yScale = (float)h / up->getSize().y;
    upSprite->setScale(xScale, yScale);
    m_background[0] = &upSprite;
    if (down)
    {
        sf::Sprite* downSprite = new sf::Sprite(*down);
        downSprite->setPosition(x, y);
        float xScale = (float)w / down->getSize().x;
        float yScale = (float)h / down->getSize().y;
        downSprite->setScale(xScale, yScale);
        m_background[1] = &downSprite;
    }
    else
    {
        m_background[1] = &upSprite;
    }
    if (hover)
    {
        sf::Sprite* hoverSprite = new sf::Sprite(*hover);
        hoverSprite->setPosition(x, y);
        float xScale = (float)w / hover->getSize().x;
        float yScale = (float)h / hover->getSize().y;
        hoverSprite->setScale(xScale, yScale);
        m_background[2] = &hoverSprite;
    }
    else
    {
        m_background[2] = &upSprite;
    }
}

Button::~Button()
{
    for (unsigned i = 0; i < 3; i++)
    {
        if (*m_background[i] != nullptr)
        {
            delete *m_background[i];
            *m_background[i] = nullptr;
        }
    }
}

void Button::setActive(bool active)
{
    m_isActive = active;
}

bool Button::isActive() { return m_isActive; }

void Button::draw(sf::RenderTarget* rt)
{
    sf::Sprite* state = *m_background[0]; //up
    if (m_isActive)
    {
        sf::Vector2i mPos = sf::Mouse::getPosition();
        if (mPos.x > x && mPos.x < x + w && mPos.y > y && mPos.y < y + h)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                state = *m_background[1]; //down
            }
            else
            {
                state = *m_background[2]; //hover
            }
        }
    }
    rt->draw(*state);
}

void Button::update()
{
    if (m_isActive)
    {
        sf::Vector2i mPos = sf::Mouse::getPosition();
        if (mPos.x > x && mPos.x < x + w && mPos.y > y && mPos.y < y + h)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (!m_isPressed)
                {
                    m_isPressed = true;
                    m_callback;
                }
            }
            else
            {
                m_isPressed = false;
            }
        }
    }
}