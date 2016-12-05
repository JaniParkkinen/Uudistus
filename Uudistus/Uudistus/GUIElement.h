#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <SFML\Graphics.hpp>

class GUIElement
{
public:
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

protected:
    int m_x, m_y, m_w, m_h;
    int m_depth;
    bool m_visible;
    sf::Color m_color;
};

#endif