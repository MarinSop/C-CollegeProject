#pragma once
#include "tinyxml/tinyxml.h"
#include <vector>
#include "Entity.h"
#include "InputManager.h"
#include "Slingshot.h"
#include <iostream>
class Level
{
public:

	Level(std::string loc, b2World* world, sf::RenderWindow* win,InputManager* input);
	~Level();


	void update();
	void draw();

	bool isGameWon();
	bool isGameLost();

	bool isRestartClicked();
	bool isMenuClicked();

private:
	void createLevel(std::string str);

	void handleDead();
	std::vector<Entity*> _woods;
	std::vector<Entity*> _stones;
	std::vector<Entity*> _pigs;
	Slingshot* _slingshot;
	b2World* _world;
	InputManager* _input;
	sf::RenderWindow* _win;
	sf::Texture* _backgroundTex;
	sf::Sprite* _backgroundSprite;
	Entity* _ground;
	float woodHealth = 100.0f;
	float stoneHealth = 200.0f;
	float pigHealth = 50.0f;
	sf::Vector2f _tiledRes;
	sf::Vector2f _gameRes;

	float lostTimer = 5.0f;
	float currLostTimer = lostTimer;

	sf::Texture* _restartTex;
	sf::Sprite* _restartSprite;
	sf::Texture* _menuTex;
	sf::Sprite* _menuSprite;
};

