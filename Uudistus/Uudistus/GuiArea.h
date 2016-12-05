#ifndef GUIAREA_H 
#define GUIAREA_H

#include "Button.h"
#include <functional>

class GUIArea
{
public:
    GUIArea(int x, int y, int w, int h, int rows, int columns = 1);
    ~GUIArea();
    void draw(sf::RenderTarget* rt);
    void update();

    void setBackground(sf::Texture* texture, float alpha = 1.0f);
    void createButton(std::string name, t_function callback, sf::Texture* up, sf::Texture* down = nullptr, sf::Texture* hover = nullptr);
    void clearButtons();
    void removeButton(std::string name);
    void setActive(bool active);
    void setActive(std::string name, bool active);
    void setVisible(bool visible);
    void setArea(int x, int y, int w, int h);
    void setBorder(int x, int y); //TODO: top, bottom, left, right margins
    void setElementMargin(int x, int y);
private:
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    int m_rows;
    int m_columns;
    int m_xElementMargin;
    int m_yElementMargin;
    int m_xBorder;
    int m_yBorder;
    bool m_isVisible;
    sf::Sprite m_background;
    std::map<std::string, GUIElement*> m_buttons;
};

#endif // ! 
