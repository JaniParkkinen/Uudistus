#include "InputManager.h"

bool InputManager::mouseDown(MouseButton button)
{
    return _mouseDown[button];
}

bool InputManager::mousePressed(MouseButton button)
{
    return _mousePressed[button];
}

bool InputManager::mouseReleased(MouseButton button)
{
    return _mouseReleased[button];
}

bool InputManager::mouseDoubleClick(MouseButton button)
{
    return _mouseDoubleClicked[button];
}

sf::Vector2f InputManager::getMousePos()
{
    return _mousePos;
}

void InputManager::update(const float dt, const sf::RenderWindow* window)
{
    //printf_s("input update\n");
    const float doubleClickMaxTime = 1.0f;

    _mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    if (_doubleClickTimer[0] > 0) { _doubleClickTimer[0] -= dt; }
    if (_doubleClickTimer[1] > 0) { _doubleClickTimer[1] -= dt; }
    if (_doubleClickTimer[2] > 0) { _doubleClickTimer[2] -= dt; }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!_mouseDown[0])
        {
            if (_doubleClickTimer[0] > 0)
            {
                _mouseDoubleClicked[0] = true;
                _doubleClickTimer[0] = -1.0f;
            }
            else
            {
                _doubleClickTimer[0] = 1.0f;
            }
        }
        _mousePressed[0] = !_mouseDown[0];
        _mouseDown[0] = true;
    }
    else
    {
        _mouseReleased[0] = _mouseDown[0];
        _mouseDown[0] = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        if (!_mouseDown[1])
        {
            if (_doubleClickTimer[1] > 0)
            {
                _mouseDoubleClicked[1] = true;
                _doubleClickTimer[1] = -1.0f;
            }
            else
            {
                _doubleClickTimer[1] = 1.0f;
            }
        }
        _mousePressed[1] = !_mouseDown[1];
        _mouseDown[1] = true;
    }
    else
    {
        _mouseReleased[1] = _mouseDown[1];
        _mouseDown[1] = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
    {
        if (!_mouseDown[2])
        {
            if (_doubleClickTimer[2] > 0)
            {
                _mouseDoubleClicked[2] = true;
                _doubleClickTimer[2] = -1.0f;
            }
            else
            {
                _doubleClickTimer[2] = 1.0f;
            }
        }
        _mousePressed[2] = !_mouseDown[2];
        _mouseDown[2] = true;
    }
    else
    {
        _mouseReleased[2] = _mouseDown[2];
        _mouseDown[2] = false;
    }
}