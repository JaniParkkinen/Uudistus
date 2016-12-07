#include "GUIText.h"

GUIText::GUIText(int x, int y, int w, int h, std::string text, sf::Font* font)
    :GUIElement(x, y, w, h)
{
    m_text.setFont(*font);
    setText(text);
    setAlignment(0);
}

void GUIText::update()
{

}

void GUIText::draw(sf::RenderTarget* rt)
{
    rt->draw(m_text);
}

void GUIText::setText(std::string text)
{
    m_text.setString(text);
    setAlignment(m_alignment);
}

void GUIText::setSize(int px)
{
    m_text.setCharacterSize(px);
    setAlignment(m_alignment);
}
void GUIText::setAlignment(int alignment)
{
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_alignment = alignment;

    switch (m_alignment)
    {
    case 0: //left
        m_text.setPosition(m_x, m_y);
        break;
    case 1: //center
        m_text.setPosition(m_x - (bounds.width / 2.f), m_y);
        break;
    case 2: //right
        m_text.setPosition(m_x - bounds.width, m_y);
        break;
    default:
        break;
    }
}