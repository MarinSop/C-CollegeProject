#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class InputManager
{
public:
	bool isMouseButtonDown(sf::Mouse::Button button);
	bool isMouseButtonDownOnce(sf::Mouse::Button button);
	bool isMouseButtonReleased(sf::Mouse::Button button);


private:
	bool isMousePressed = false;
};

