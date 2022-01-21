#include "Entity.h"

Entity::Entity(b2World* world, sf::RenderWindow* win,float health, std::string loc, b2BodyType type, b2Vec2 position, b2Vec2 size,std::string data)
{
	_world = world;
	_win = win;
	_data = new UserData(this, data);
	_physicalBody = new PhysicalBody(_world, type, position, size,_data);
	_graphicalBody = new GraphicalBody(loc, sf::Vector2f(position.x, position.y), sf::Vector2f(size.x, size.y));
	_maxHealth = health;
	_currentHealth = _maxHealth;
}

Entity::Entity(b2World* world, sf::RenderWindow* win, float health, std::string loc, b2BodyType type, b2Vec2 position, b2Vec2 size, float radius,std::string data)
{
	_world = world;
	_win = win;
	_data = new UserData(this,data);
	_physicalBody = new PhysicalBody(_world, type, position,radius,_data);
	_graphicalBody = new GraphicalBody(loc, sf::Vector2f(position.x, position.y), sf::Vector2f(size.x, size.y),radius);
	_maxHealth = health;
	_currentHealth = _maxHealth;
}

Entity::Entity(b2World* world, sf::RenderWindow* win,float health, sf::Color color, b2BodyType type, b2Vec2 position, b2Vec2 size)
{
	_world = world;
	_win = win;
	_physicalBody = new PhysicalBody(_world, type, position, size);
	_graphicalBody = new GraphicalBody(color, sf::Vector2f(position.x, position.y), sf::Vector2f(size.x, size.y));
	_maxHealth = health;
	_currentHealth = _maxHealth;
}

Entity::~Entity()
{
	delete _graphicalBody;
	delete _physicalBody;
	delete _data;
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

b2Vec2 Entity::getLinearVelocity()
{
	return _physicalBody->getLinearVelocity();
}

void Entity::takeDamage(float damage)
{
	_currentHealth -= damage;
	if (_currentHealth <= 0)
		dead = true;
}

bool Entity::isDead()
{
	if (dead)
		delete this;
	return dead;
}

