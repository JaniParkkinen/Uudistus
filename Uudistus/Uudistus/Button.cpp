#include "Button.h"
#include "InputManager.h"

Button::Button(int x, int y, int w, int h, t_function callback, sf::Texture* up, sf::Texture* down, sf::Texture* hover)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    callback();

    m_isActive = true;
    m_callback = callback;
    m_isPressed = false;

    m_bgSprite = sf::Sprite(*up);
    m_bgSprite.setPosition(x, y);
    float xScale = (float)w / up->getSize().x;
    float yScale = (float)h / up->getSize().y;
    m_bgSprite.setScale(xScale, yScale);
    //sf::Sprite** upPtr = &upSprite;
    m_bgTexture[0] = up;
    if(down)
        m_bgTexture[1] = down;
    else
        m_bgTexture[1] = up;
    if (hover)
        m_bgTexture[2] = hover;
    else
        m_bgTexture[2] = up;
}

Button::~Button()
{
}

void Button::setActive(bool active)
{
    m_isActive = active;
}

bool Button::isActive() { return m_isActive; }

void Button::draw(sf::RenderTarget* rt)
{
    if (m_isActive)
    {
        sf::Vector2f mPos = InputManager::instance()->getMousePos();
        if (mPos.x > x && mPos.x < x + w && mPos.y > y && mPos.y < y + h)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                //down
                if (m_bgSprite.getTexture() != m_bgTexture[1])
                    m_bgSprite.setTexture(*m_bgTexture[1], true); 
                rt->draw(m_bgSprite);
                return;
            }
            else
            {
                //hover
                if (m_bgSprite.getTexture() != m_bgTexture[2])
                    m_bgSprite.setTexture(*m_bgTexture[2], true);
                rt->draw(m_bgSprite);
                return;
            }
        }
    }
    if (m_bgSprite.getTexture() != m_bgTexture[0])
        m_bgSprite.setTexture(*m_bgTexture[0], true);
    rt->draw(m_bgSprite);
}

void Button::update()
{
    if (m_isActive)
    {
        sf::Vector2f mPos = InputManager::instance()->getMousePos();
        if (mPos.x > x && mPos.x < x + w && mPos.y > y && mPos.y < y + h)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (!m_isPressed)
                {
                    printf_s("Calling back...\n");
                    m_isPressed = true;
                    m_callback();
                }
            }
            else
            {
                m_isPressed = false;
            }
        }
    }
}