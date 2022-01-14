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

	void createLevel(std::string str);

	void update();
	void draw();

private:
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
};

