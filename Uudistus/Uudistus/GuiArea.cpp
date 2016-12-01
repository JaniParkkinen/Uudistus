#include "GuiArea.h"

GUIArea::GUIArea(int x, int y, int w, int h, int rows, int columns)
    :m_x(x),
    m_y(y),
    m_w(w),
    m_h(h)
{
    m_background = sf::Sprite();
    m_background.setPosition(x, y);
    m_isVisible = true;
}

GUIArea::~GUIArea()
{
   //nothing here yet
}

void GUIArea::draw(sf::RenderTarget* rt)
{
    if (m_isVisible)
    {
        rt->draw(m_background);
        for (std::pair<std::string, Button> b : m_buttons)
        {
            b.second.draw(rt);
        }
    }
}

void GUIArea::update()
{
    if (m_isVisible)
    {
        for (std::pair<std::string, Button> b : m_buttons)
        {
            b.second.update();
        }
    }
}

void GUIArea::setBackground(sf::Texture texture, float alpha)
{
    m_background.setTexture(texture);
    m_background.setColor(sf::Color(255, 255, 255, 255 * alpha));
    float xScale = (float)m_w / texture.getSize().x;
    float yScale = (float)m_h / texture.getSize().y;
    m_background.setScale(xScale, yScale);
}

void GUIArea::createButton(std::string name, sf::Texture* buttons, t_function callback)
{
    int size = m_buttons.size();
    int x = m_x + (m_columns % size) * m_w;
    int y = m_y + (size / m_rows) * m_h;

    m_buttons.insert(std::make_pair(name, Button(m_x, m_y, m_w / m_columns, m_h / m_rows, callback, buttons)));
}

void GUIArea::clearButtons()
{
    m_buttons.clear();
}

void GUIArea::removeButton(std::string name)
{
    m_buttons.erase("name");
}

void GUIArea::setActive(bool active)
{
    for (std::pair<std::string, Button> b : m_buttons)
    {
        b.second.setActive(active);
    }
}

void GUIArea::setActive(bool active)
{
    for (std::pair<std::string, Button> b : m_buttons)
    {
        b.second.setActive(active);
    }
}

void GUIArea::setActive(std::string name, bool active)
{
    m_buttons[name].setActive(active);
}

void GUIArea::setVisible(bool visible)
{
    m_isVisible = visible;
}

void GUIArea::setArea(int x, int y, int w, int h)
{
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
    m_background.setPosition(x, y);
    float xScale = (float)m_w / m_background.getTexture()->getSize().x;
    float yScale = (float)m_h / m_background.getTexture()->getSize().y;
    m_background.setScale(xScale, yScale);
}