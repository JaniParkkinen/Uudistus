#include "GuiArea.h"

GUIArea::GUIArea(int x, int y, int w, int h, int rows, int columns)
    :m_x(x),
    m_y(y),
    m_w(w),
    m_h(h),
    m_rows(rows),
    m_columns(columns)
{
    m_background = sf::Sprite();
    m_background.setPosition(x, y);
    m_isVisible = true;
}

GUIArea::~GUIArea()
{
    for (std::pair<std::string, GUIElement*> b : m_buttons)
    {
        delete b.second;
    }
}

void GUIArea::draw(sf::RenderTarget* rt)
{
    if (m_isVisible)
    {
        rt->draw(m_background);
        for (std::pair<std::string, GUIElement*> b : m_buttons)
        {
            b.second->draw(rt);
        }
    }
}

void GUIArea::update()
{
    if (m_isVisible)
    {
        for (std::pair<std::string, GUIElement*> b : m_buttons)
        {
            b.second->update();
        }
    }
}

void GUIArea::setBackground(sf::Texture* texture, float alpha)
{
    m_background.setTexture(*texture, true);
    m_background.setColor(sf::Color(255, 255, 255, 255 * alpha));
    float xScale = (float)m_w / texture->getSize().x;
    float yScale = (float)m_h / texture->getSize().y;
    m_background.setScale(xScale, yScale);
}

void GUIArea::createButton(std::string name, t_function callback, sf::Texture* up, sf::Texture* down, sf::Texture* hover)
{
    int elementW = (m_w - m_xBorder * 2 - (m_xElementMargin * (m_columns - 1))) / m_columns;
    int elementH = (m_h - m_yBorder * 2 - (m_yElementMargin * (m_rows - 1))) / m_rows;

    int size = m_buttons.size();
    int x = m_x + m_xBorder + (elementW + m_xElementMargin) * (size % m_columns);
    int y = m_y + m_yBorder + (elementH + m_yElementMargin) * (size / m_columns);

    Button* button = new Button(x, y, elementW, elementH, callback, up, down, hover);
    //std::pair<std::string, Button*> buttonPair(name, button);
    //m_buttons.insert(buttonPair);

    button->setActive(true);

    m_buttons[name] = button;

    //m_buttons.emplace(name, button);
}

void GUIArea::clearButtons()
{
    m_buttons.clear();
}

void GUIArea::removeButton(std::string name)
{
    //delete m_buttons[name];
    m_buttons.erase(name);
}

void GUIArea::setActive(bool active)
{
    for (std::pair<std::string, GUIElement*> b : m_buttons)
    {
        b.second->setActive(active);
    }
}

void GUIArea::setActive(std::string name, bool active)
{
    m_buttons[name]->setActive(active);
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

void GUIArea::setBorder(int x, int y)
{
    m_xBorder = x;
    m_yBorder = y;
}

void GUIArea::setElementMargin(int x, int y)
{
    m_xElementMargin = x;
    m_yElementMargin = y;
}