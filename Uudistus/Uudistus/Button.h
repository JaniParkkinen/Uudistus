#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>

#include <functional>
typedef std::function<void(void)> t_function;

class Button
{
public:
    Button(int x, int y, int w, int h, t_function callback, sf::Texture* up, sf::Texture* down = nullptr, sf::Texture* hover = nullptr);
    ~Button();

    void setActive(bool active);
    bool isActive();

    void draw(sf::RenderTarget* rt);
    void update();
private:
    int x, y, w, h;
    bool m_isActive;
    bool m_isPressed;
    sf::Sprite** m_background[3];
    t_function m_callback;
};

#endif