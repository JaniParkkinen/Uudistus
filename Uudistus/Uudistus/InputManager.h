#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

enum MouseButton
{
    Left,
    Right,
    Middle
};

class InputManager
{
public:
    static InputManager* instance();

    bool mouseDown(MouseButton button);
    bool mousePressed(MouseButton button);
    bool mouseReleased(MouseButton button);
    bool mouseDoubleClick(MouseButton button);

    sf::Vector2f getMousePos();

    void update(const float dt, const sf::RenderWindow* window);

private:
    InputManager();

    static InputManager* _instance;

    bool _mousePressed[3];
    bool _mouseDoubleClicked[3];
    bool _mouseReleased[3];
    bool _mouseDown[3];
    float _doubleClickTimer[3];
    sf::Vector2f _mousePos;
};
