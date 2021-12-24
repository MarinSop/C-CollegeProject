#pragma once
#include "PhysicalBody.h"
#include "GraphicalBody.h"
class Bird
{
public:
	Bird(sf::RenderWindow* win,std::string loc, b2World* world, b2BodyType type, b2Vec2 position, b2Vec2 size);
	Bird(sf::RenderWindow* win, std::string loc, b2World* world, b2BodyType type, b2Vec2 position, b2Vec2 size,float radius);
	~Bird();
	void update();
	void draw();

	void applyLinearImpulse(b2Vec2 impulse);
	float getMass();
	bool isUsed();
	bool isReady();
	void setReady(bool state);
	void setUsed(bool state);
	bool readyToDelete();
	void setPosition(b2Vec2 pos);
	void setEnabled(bool state);

private:
	PhysicalBody* _physicalBody;
	GraphicalBody* _graphicalBody;
	sf::RenderWindow* _win;
	float _selfDestructTimerMax = 5.0f;
	float _selfDestructTimerCurrent = 0.0f;
	bool _used = false;
	bool _ready = false;

};

