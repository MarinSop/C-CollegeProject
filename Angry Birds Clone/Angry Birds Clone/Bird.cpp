#include "Bird.h"


Bird::Bird(sf::RenderWindow* win, std::string loc, b2World* world, b2BodyType type, b2Vec2 position, b2Vec2 size)
{
	_win = win;
	_physicalBody = new PhysicalBody(world, type, position, size);
	_graphicalBody = new GraphicalBody("Sprites/red.png", sf::Vector2f(position.x, position.y), sf::Vector2f(size.x, size.y));
	_physicalBody->setAwake(false);
	ready = true;
	shotPred = sf::VertexArray(sf::LineStrip, 10);
	startPos = _physicalBody->getPosition();
}

void Bird::update()
{
	_graphicalBody->setPosition(sf::Vector2f(_physicalBody->getPositionScaled().x, _physicalBody->getPositionScaled().y));
	_graphicalBody->setRotation(_physicalBody->getAngle() * 180 / b2_pi);
	applyForce();
}

void Bird::draw()
{
	_graphicalBody->draw(*_win);
}

void Bird::applyForce()
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		startPos = _physicalBody->getPosition();
		_impulse = b2Vec2(startPos.x - sf::Mouse::getPosition(*_win).x, startPos.y - sf::Mouse::getPosition(*_win).y);

		int j = 1;
		for (int i = 0; i < 10; i++)
		{
			sf::Vector2f trajectoryPosition = getTrajectoryPoint(_physicalBody->getPosition(), _impulse, j);
			j += 20;
			std::cout << "x: " << trajectoryPosition.x * SCALE << "y: " << trajectoryPosition.y * SCALE << std::endl;
			shotPred[i] = sf::Vector2f(trajectoryPosition.x * SCALE, trajectoryPosition.y * SCALE);
		}
		_win->draw(shotPred);
		if (_graphicalBody->getPosition().x - _graphicalBody->getSize().x / 2 < sf::Mouse::getPosition(*_win).x &&
			_graphicalBody->getPosition().x + _graphicalBody->getSize().x / 2 > sf::Mouse::getPosition(*_win).x &&
			_graphicalBody->getPosition().y - _graphicalBody->getSize().y / 2 < sf::Mouse::getPosition(*_win).y &&
			_graphicalBody->getPosition().y + _graphicalBody->getSize().y > sf::Mouse::getPosition(*_win).y)
		{
			if (!mousePress && ready)
			{
				_physicalBody->applyImpulse(b2Vec2(15.0f, -5.0f));
				mousePress = true;
				ready = false;
			}
		}
	}
	else
		mousePress = false;

}

sf::Vector2f Bird::getTrajectoryPoint(b2Vec2 startingPosition, b2Vec2 startingVelocity, int n)
{
	b2Vec2 gravity = _physicalBody->getWorld()->GetGravity();
	float t = 1 / 60.0f;
	float x = startPos.x + _impulse.x / _physicalBody->bd()->GetMass() * t*n + (t*t*gravity.x) * n * n / 2;
	float y = startPos.y + _impulse.y / _physicalBody->bd()->GetMass() * t*n + (t*t*gravity.y) * n * n / 2;
	return sf::Vector2f(x, y);

}
