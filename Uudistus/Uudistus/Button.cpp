#include "Button.h"
#include "InputManager.h"

Button::Button(int x, int y, int w, int h, t_function callback, sf::Texture* up, sf::Texture* down, sf::Texture* hover)
    :GUIElement(x, y, w, h)
{

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

void Button::setColor(sf::Color color)
{
    m_color = color;
    m_bgSprite.setColor(m_color);
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
        sf::Vector2i mPos = InputManager::instance()->getMousePosWindow();
        if (mPos.x > m_x && mPos.x < m_x + m_w && mPos.y > m_y && mPos.y < m_y + m_h)
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
        if (mPos.x > m_x && mPos.x < m_x + m_w && mPos.y > m_y && mPos.y < m_y + m_h)
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