#pragma once
#include <vector>
#include "Bird.h"
#include "InputManager.h"
class Slingshot
{
public:
	Slingshot(sf::RenderWindow* win,InputManager* input,b2World* world, std::string str,sf::Vector2f position,sf::Vector2f size);
	~Slingshot();

	void draw();
	void update();
	sf::Vector2f getTrajectoryPoint(b2Vec2 impulse, int n);
	void setTrajectoryPointsPosition(b2Vec2 impulse);
	void slingControl();

	bool areBirdsUsed();

private:
	std::vector<Bird*> _birds;
	sf::Texture* _texMain;
	sf::Sprite* _spriteMain;
	sf::Texture* _texOther;
	sf::Sprite* _spriteOther;
	sf::RenderWindow* _win;
	b2World* _world;
	sf::Vector2f _birdShootPosition;
	sf::Vector2f _birdRestPosition;
	float _maxStrech = 150.0f;
	float _maxForce = 20.0f;
	std::vector<sf::CircleShape> _trajectoryPoints;
	InputManager* _input;
	b2Vec2 impulse;
	bool _aiming = false;
	Bird* activeBird;
	std::vector<Bird*> _usedBirds;
};

