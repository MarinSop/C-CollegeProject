#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include <iostream>
class MainMenu
{
public:
	MainMenu(sf::RenderWindow* win, InputManager* input,int lvl);
	~MainMenu();


	bool isPlayClicked();
	bool isExitClicked();
	bool isRightClicked();
	bool isLeftClicked();
	void draw();

private:
	sf::RenderWindow* _win;
	InputManager* _input;

	sf::Texture* _playTex;
	sf::Sprite* _playSprite;

	sf::Texture* _exitTex;
	sf::Sprite* _exitSprite;

	sf::Texture* _leftTex;
	sf::Sprite* _leftSprite;

	sf::Texture* _rightTex;
	sf::Sprite* _rightSprite;

	sf::Texture* _textboxTex;
	sf::Sprite* _textboxSprite;

	sf::Text* _text;
	sf::Font* _font;

	int lvlNum;
};

