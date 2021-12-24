#include "InputManager.h"

bool InputManager::isMouseButtonDown(sf::Mouse::Button button)
{
    if (sf::Mouse::isButtonPressed(button))
    {
        return true;
    }
    return false;
}

bool InputManager::isMouseButtonDownOnce(sf::Mouse::Button button)
{
    if(sf::Mouse::isButtonPressed(button) && !isMousePressed)
    {
        isMousePressed = true;
        return true;
    }
    else if (sf::Mouse::isButtonPressed(button) && isMousePressed)
    {
        return false;
    }
    isMousePressed = false;
    return false;
}

bool InputManager::isMouseButtonReleased(sf::Mouse::Button button)
{
    if (!sf::Mouse::isButtonPressed(button) && isMousePressed)
    {
        isMousePressed = false;
        return true;
    }
    else if (sf::Mouse::isButtonPressed(button))
    {
        isMousePressed = true;
        return false;
    }
    return false;
}
