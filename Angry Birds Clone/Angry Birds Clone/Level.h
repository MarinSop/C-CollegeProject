#pragma once
#include "tinyxml/tinyxml.h"
#include <vector>
#include "Entity.h"
#include <iostream>
class Level
{
public:

	Level(std::string loc, b2World* world, sf::RenderWindow* win);
	~Level();

	void createLevel(std::string str);

	void update();
	void draw();

private:
	std::vector<Entity*> _woods;
	std::vector<Entity*> _stones;
	b2World* _world;
	sf::RenderWindow* _win;
	float woodHealth = 100.0f;
	float stoneHealth = 200.0f;
};

