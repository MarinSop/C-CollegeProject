#pragma once
#include "PhysicalBody.h"
#include "GraphicalBody.h"
#include <iostream>
class Entity
{
public:
	Entity(b2World* world,sf::RenderWindow* win,float health, std::string loc, b2BodyType type, b2Vec2 position, b2Vec2 size,std::string data = "NaN");
	Entity(b2World* world, sf::RenderWindow* win, float health, std::string loc, b2BodyType type, b2Vec2 position, b2Vec2 size, float radius, std::string data = "NaN");
	Entity(b2World* world, sf::RenderWindow* win,float health, sf::Color color, b2BodyType type, b2Vec2 position, b2Vec2 size);
	~Entity();

	void update();
	void draw();
	b2Vec2 getLinearVelocity();
	void takeDamage(float damage);
	bool isDead();
private:
	sf::RenderWindow* _win;
	b2World* _world;
	PhysicalBody* _physicalBody;
	GraphicalBody* _graphicalBody;
	float _maxHealth;
	float _currentHealth = _maxHealth;
	UserData* _data;
	bool dead = false;
};

