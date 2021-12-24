#include "Entity.h"

Entity::Entity(b2World* world, sf::RenderWindow* win, std::string loc, b2BodyType type, b2Vec2 position, b2Vec2 size)
{
}

Entity::Entity(b2World* world, sf::RenderWindow* win,float health, sf::Color color, b2BodyType type, b2Vec2 position, b2Vec2 size)
{
	_world = world;
	_win = win;
	_physicalBody = new PhysicalBody(_world, type, position, size);
	_graphicalBody = new GraphicalBody(color, sf::Vector2f(position.x, position.y), sf::Vector2f(size.x, size.y));
	_maxHealth = health;
}

Entity::~Entity()
{
	delete _graphicalBody;
	delete _physicalBody;
}

void Entity::update()
{
	_graphicalBody->setPosition(sf::Vector2f(_physicalBody->getPositionScaled().x, _physicalBody->getPositionScaled().y));
	_graphicalBody->setRotation(_physicalBody->getAngle() * 180 / b2_pi);
}

void Entity::draw()
{
	_graphicalBody->draw(*_win);
}