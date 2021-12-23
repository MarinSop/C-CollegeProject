#pragma once
#include "PhysicalBody.h"
#include "GraphicalBody.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Bird
{
public:
	Bird(sf::RenderWindow* win,std::string loc, b2World* world, b2BodyType type, b2Vec2 position, b2Vec2 size);

	void update();
	void draw();

	void applyForce();
	sf::Vector2f getTrajectoryPoint(b2Vec2 startingPosition,b2Vec2 startingVelocity,int n);

private:
	PhysicalBody* _physicalBody;
	GraphicalBody* _graphicalBody;
	bool ready = false;
	bool mousePress = false;
	sf::RenderWindow* _win;
	sf::VertexArray shotPred;
	b2Vec2 startPos;
	b2Vec2 _impulse;
};

