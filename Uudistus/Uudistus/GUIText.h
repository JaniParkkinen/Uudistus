#ifndef GUI_TEXT_H
#define GUI_TEXT_H

#include "GUIElement.h"

class GUIText : public GUIElement
{
public:
    GUIText(int x, int y, int w, int h, std::string text, sf::Font* font);
    virtual void update()override;
    virtual void draw(sf::RenderTarget* rt)override;

    void setText(std::string text);
    void setSize(int px);
    void setAlignment(int alignment);
private:
    int m_size;
    int m_alignment;
    sf::Text m_text;
};

#endif