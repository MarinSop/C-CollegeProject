#include "GraphicalBody.h"

GraphicalBody::GraphicalBody(std::string str, sf::Vector2f position, sf::Vector2f size)
{
	_size = size;
	_tex = new sf::Texture();
	_tex->loadFromFile(str);
	_sprite = new sf::Sprite(*_tex);
	_collision = new sf::RectangleShape();
	_sprite->setOrigin(_tex->getSize().x / 2, _tex->getSize().y / 2);
	_sprite->setPosition(sf::Vector2f(position.x, position.y));
	_sprite->setScale((1.0f / _tex->getSize().x) * size.x, (1.0f / _tex->getSize().y) * size.y);
	_collision->setSize(sf::Vector2f(size.x, size.y));
	_collision->setOrigin(sf::Vector2f(size.x / 2.0f, size.y / 2.0f));
	_collision->setFillColor(sf::Color::Transparent);
	_collision->setOutlineColor(sf::Color::Green);
	_collision->setOutlineThickness(2.0f);
}

GraphicalBody::~GraphicalBody()
{
	delete _collision;
	delete _sprite;
	delete _tex;
}

void GraphicalBody::setPosition(sf::Vector2f pos)
{
	_sprite->setPosition(pos);
	_collision->setPosition(pos);
}

sf::Vector2f GraphicalBody::getPosition()
{
	return _sprite->getPosition();;
}

sf::Vector2f GraphicalBody::getSize()
{
	return _size;
}

void GraphicalBody::setRotation(float angle)
{
	_sprite->setRotation(angle);
	_collision->setRotation(angle);
}

void GraphicalBody::draw(sf::RenderWindow& win)
{
	win.draw(*_sprite);
	win.draw(*_collision);
}

