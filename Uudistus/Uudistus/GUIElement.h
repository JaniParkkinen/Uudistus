#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <SFML\Graphics.hpp>

class GUIElement
{
public:
    GUIElement(int x, int y, int w, int h)
    {
        m_x = x;
        m_y = y;
        m_w = w;
        m_h = h;
        m_depth = 0;
        m_visible = true;
        m_color = sf::Color::White;
    }

    virtual bool operator<(GUIElement& other)
    {
        return m_depth < other.m_depth;
    }

    virtual bool operator>(GUIElement& other)
    {
        return m_depth > other.m_depth;
    }

    virtual void update() = 0;
    virtual void draw(sf::RenderTarget* rt) = 0;

    virtual void setColor(sf::Color color)
    {
        m_color = color;
    }

protected:
    int m_x, m_y, m_w, m_h;
    int m_depth;
    bool m_visible;
    sf::Color m_color;
};

#endif