#include "GuiArea.h"
#include "GUIText.h"

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
    rt->setView(rt->getDefaultView());
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
    std::vector<std::string> removed;

    if (m_isVisible)
    {
        for (std::pair<std::string, GUIElement*> b : m_buttons)
        {
            b.second->update();
            if (b.second->isRemoved())
            {
                removed.push_back(b.first);
            }
        }
    }
    for (unsigned i = 0; i < removed.size(); i++)
    {
        m_buttons.erase(removed[i]);
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

    button->setActive(true);

    m_buttons[name] = button;
}

void GUIArea::createText(std::string name, std::string text, sf::Font* font)
{
    int elementW = (m_w - m_xBorder * 2 - (m_xElementMargin * (m_columns - 1))) / m_columns;
    int elementH = (m_h - m_yBorder * 2 - (m_yElementMargin * (m_rows - 1))) / m_rows;

    int size = m_buttons.size();
    int x = m_x + m_xBorder + (elementW + m_xElementMargin) * (size % m_columns);
    int y = m_y + m_yBorder + (elementH + m_yElementMargin) * (size / m_columns);

    GUIText* guiText = new GUIText(x, y, elementW, elementH, text, font);
    m_buttons[name] = guiText;
}


void GUIArea::clearButtons()
{
    //m_buttons.clear();
    for (std::pair<std::string, GUIElement*> b : m_buttons)
    {
        b.second->remove();
    }
}

void GUIArea::removeElement(std::string name)
{
    //delete m_buttons[name];
    //m_buttons.erase(name);
    m_buttons[name]->remove();
}

void GUIArea::setButtonActive(bool active)
{
    for (std::pair<std::string, GUIElement*> b : m_buttons)
    {
        Button* button = dynamic_cast<Button*>(b.second);
        if(button)
            button->setActive(active);
    }
}

void GUIArea::setButtonActive(std::string name, bool active)
{
    Button* b = dynamic_cast<Button*>(m_buttons[name]);
    if (b)
        b->setActive(active);
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