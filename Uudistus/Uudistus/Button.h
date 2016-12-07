#ifndef BUTTON_H
#define BUTTON_H

//#include <SFML\Graphics.hpp>
#include "GUIElement.h"

#include <functional>
typedef std::function<void(void)> t_function;

class Button : public GUIElement
{
public:
    Button(int x, int y, int w, int h, t_function callback, sf::Texture* up, sf::Texture* down = nullptr, sf::Texture* hover = nullptr);
    ~Button();

    void setColor(sf::Color color)override;
    void setActive(bool active);
    bool isActive();

    void draw(sf::RenderTarget* rt);
    void update();

private:
    //int x, y, w, h;
    bool m_isActive;
    bool m_isPressed;
    sf::Texture* m_bgTexture[3];
    sf::Sprite m_bgSprite;
    t_function m_callback;
};

#endif