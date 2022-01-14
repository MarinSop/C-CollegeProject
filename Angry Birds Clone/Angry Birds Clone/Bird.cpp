#include "Bird.h"


Bird::Bird(sf::RenderWindow* win, std::string loc, b2World* world, b2BodyType type, b2Vec2 position, b2Vec2 size)
{
	_win = win;
	_physicalBody = new PhysicalBody(world, type, position, size);
	_graphicalBody = new GraphicalBody("Sprites/red.png", sf::Vector2f(position.x, position.y), sf::Vector2f(size.x, size.y));
	_physicalBody->setAwake(false);
}

Bird::Bird(sf::RenderWindow* win, std::string loc, b2World* world, b2BodyType type, b2Vec2 position, b2Vec2 size, float radius)
{
	_win = win;
	_physicalBody = new PhysicalBody(world, type, position, radius);
	_graphicalBody = new GraphicalBody("Sprites/red.png", sf::Vector2f(position.x, position.y), sf::Vector2f(size.x, size.y),radius);
	_physicalBody->setAwake(false);
}

Bird::~Bird()
{
	delete _physicalBody;
	delete _graphicalBody;
}

void Bird::update()
{
	_graphicalBody->setPosition(sf::Vector2f(_physicalBody->getPositionScaled().x, _physicalBody->getPositionScaled().y));
	_graphicalBody->setRotation(_physicalBody->getAngle() * 180 / b2_pi);
}

void Bird::draw()
{
	_graphicalBody->draw(*_win);
}


void Bird::applyLinearImpulse(b2Vec2 impulse)
{
	_physicalBody->applyImpulse(impulse);
}

float Bird::getMass()
{
	return _physicalBody->getMass();;
}

bool Bird::isUsed()
{
	return _used;
}

bool Bird::isReady()
{
	return _ready;
}

void Bird::setReady(bool state)
{
	_ready = state;
}

void Bird::setUsed(bool state)
{
	_used = state;
}

bool Bird::readyToDelete()
{

	if (_used && !_physicalBody->isAwake())
	{
		if (_selfDestructTimerCurrent >= _selfDestructTimerMax)
		{
			return true;
		}
		else
			_selfDestructTimerCurrent += 1 / 60.0f;
	}
	else if (_used && _physicalBody->getPositionScaled().y > _win->getSize().y)
		return true;
	return false;
}

void Bird::setPosition(b2Vec2 pos)
{
	_physicalBody->setPosition(pos);
}

void Bird::setEnabled(bool state)
{
	_physicalBody->setEnabled(state);
}


