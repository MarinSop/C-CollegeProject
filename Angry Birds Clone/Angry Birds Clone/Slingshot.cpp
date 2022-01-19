#include "Slingshot.h"

Slingshot::Slingshot(sf::RenderWindow* win,InputManager* input, b2World* world, std::string str, sf::Vector2f position, sf::Vector2f size)
{
	_win = win;
	_world = world;
	_input = input;
	_birdShootPosition = sf::Vector2f(position.x, position.y - 50);
	_birdRestPosition = sf::Vector2f(position.x-10.0f, position.y+50.0f);
	_texMain = new sf::Texture();
	_texMain->loadFromFile("Sprites/slingshot1.png");
	_texMain->setSmooth(true);
	_spriteMain = new sf::Sprite(*_texMain);
	_spriteMain->setOrigin(sf::Vector2f(_texMain->getSize().x / 2.0f, _texMain->getSize().y / 2.0f));
	_spriteMain->setPosition(position);
	_spriteMain->setScale(sf::Vector2f((1.0f / _texMain->getSize().x) * size.x, (1.0f / _texMain->getSize().y) * size.y));
	_texOther = new sf::Texture();
	_texOther->loadFromFile("Sprites/slingshot2.png");
	_texOther->setSmooth(true);
	_spriteOther = new sf::Sprite(*_texOther);
	_spriteOther->setOrigin(sf::Vector2f(_texOther->getSize().x / 2.0f, _texOther->getSize().y / 2.0f));
	_spriteOther->setPosition(position);
	_spriteOther->setScale(sf::Vector2f((1.0f / _texOther->getSize().x) * size.x, (1.0f / _texOther->getSize().y) * size.y));
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			Bird* bird = new Bird(_win, "Sprites/red.png", _world, b2_dynamicBody, b2Vec2(_birdShootPosition.x, _birdShootPosition.y), b2Vec2(32.0f, 32.0f), 32.0f);
			activeBird = bird;
			activeBird->setReady(true);
			activeBird->setEnabled(false);
			_birds.push_back(bird);
		}
		else
		{
			Bird* bird = new Bird(_win, "Sprites/red.png", _world, b2_dynamicBody, b2Vec2(_birdRestPosition.x - i*20.0f, _birdRestPosition.y), b2Vec2(32.0f, 32.0f),32.0f);
			bird->setEnabled(false);
			_birds.push_back(bird);
		}
	}
	for (int i = 0; i < 5; i++)
	{
		float radius = 5.0f - i * 1.0f;
		sf::CircleShape point;
		point.setFillColor(sf::Color::White);
		point.setRadius(radius);
		point.setOutlineColor(sf::Color::Black);
		point.setOutlineThickness(1);
		point.setOrigin(sf::Vector2f(radius / 2.0f, radius / 2.0f));
		_trajectoryPoints.push_back(point);
	}
}

Slingshot::~Slingshot()
{
	delete _spriteMain;
	delete _texMain;
	delete _spriteOther;
	delete _texOther;
	int birdSize = _birds.size();
	for (int i = 0; i < birdSize; i++)
	{
		delete _birds[i];
	}
}

void Slingshot::draw()
{
	_win->draw(*_spriteMain);
	int birdSize = _birds.size();
	for (int i = 0; i < birdSize; i++)
	{
		_birds[i]->draw();
	}
	int usedSize = _usedBirds.size();
	for (int i = 0; i < usedSize; i++)
	{
		_usedBirds[i]->draw();
	}
	
	if (_aiming)
	{
		int traVecSize = _trajectoryPoints.size();
		for (int i = 0; i < traVecSize; i++)
		{
			_win->draw(_trajectoryPoints[i]);
		}
	}
	_win->draw(*_spriteOther);
}

void Slingshot::update()
{
	int birdSize = _birds.size();
	for (int i = 0; i < birdSize; i++)
	{
		_birds[i]->update();
	}
	int usedSize = _usedBirds.size();
	for (int i = 0; i <  usedSize; i++)
	{
			_usedBirds[i]->update();
			if (_usedBirds[i]->readyToDelete())
			{
				delete _usedBirds[i];
				_usedBirds.erase(_usedBirds.begin() + i);
				break;
			}
	}
	slingControl();
}

sf::Vector2f Slingshot::getTrajectoryPoint(b2Vec2 impulse, int n)
{
	b2Vec2 gravity = _world->GetGravity();
	float t = 1 / 60.0f;
	float x = _birdShootPosition.x/SCALE + impulse.x / activeBird->getMass() * t * n + (t * t * gravity.x) * n * n / 2;
	float y = _birdShootPosition.y/SCALE + impulse.y / activeBird->getMass() * t * n + (t * t * gravity.y) * n * n / 2;
	return sf::Vector2f(x, y);

}

void Slingshot::setTrajectoryPointsPosition(b2Vec2 impulse)
{
	int size = _trajectoryPoints.size();
	int j = 5;
	for (int i = 0; i < size; i++)
	{
		sf::Vector2f trajectoryPosition = getTrajectoryPoint(impulse, j);
		j += 10;
		_trajectoryPoints[i].setPosition(sf::Vector2f(trajectoryPosition.x * SCALE, trajectoryPosition.y * SCALE));
	}
}

void Slingshot::slingControl()
{
	if (activeBird)
	{
		if (_input->isMouseButtonDown(sf::Mouse::Left))
		{
			_aiming = true;
			float dX = sf::Mouse::getPosition(*_win).x - _birdShootPosition.x;
			float dY = sf::Mouse::getPosition(*_win).y - _birdShootPosition.y;
			double angleRad = atan2(dY, dX);
			if (angleRad < 0)
				angleRad = abs(angleRad);
			else
				angleRad = 2 * b2_pi - angleRad;
			double angleDeg = angleRad * 180 / b2_pi;
			if (angleDeg < 115.0f)
				angleDeg = 115.0f;
			else if (angleDeg > 255.0f)
				angleDeg = 255.0f;
			float distance = sqrt(((sf::Mouse::getPosition(*_win).x - _birdShootPosition.x) * (sf::Mouse::getPosition(*_win).x - _birdShootPosition.x)) + ((sf::Mouse::getPosition(*_win).y - _birdShootPosition.y) * (sf::Mouse::getPosition(*_win).y - _birdShootPosition.y)));
			if (distance > _maxStrech)
				distance = _maxStrech;
			float force = (distance / _maxStrech) * _maxForce;
			impulse = b2Vec2(force * sin(angleDeg * (b2_pi / 180) - b2_pi / 2), force * cos(angleDeg * (b2_pi / 180) - b2_pi / 2));
			setTrajectoryPointsPosition(impulse);
		}
		else
			_aiming = false;
		if (_input->isMouseButtonReleased(sf::Mouse::Left))
		{
			activeBird->setEnabled(true);
			activeBird->applyLinearImpulse(impulse);
			activeBird->setUsed(true);
			for (int i = 0; i < _birds.size(); i++)
			{
				if (activeBird == _birds[i])
				{
					_usedBirds.push_back(_birds[i]);
					_birds.erase(_birds.begin() + i);
					activeBird = nullptr;
					if (!_birds.empty())
					{
						activeBird = _birds[0];
						activeBird->setPosition(b2Vec2(_birdShootPosition.x / SCALE, _birdShootPosition.y / SCALE));
					}
					break;
				}
			}
		}
	}
}
