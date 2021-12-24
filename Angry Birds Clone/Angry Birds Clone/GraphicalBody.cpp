#include "GraphicalBody.h"

GraphicalBody::GraphicalBody(std::string str, sf::Vector2f position, sf::Vector2f size)
{
	_size = size;
	_tex = new sf::Texture();
	_tex->loadFromFile(str);
	_sprite = new sf::Sprite(*_tex);
	_collision = new sf::RectangleShape();
	_sprite->setOrigin(_tex->getSize().x / 2.0f, _tex->getSize().y / 2.0f);
	_sprite->setPosition(sf::Vector2f(position.x, position.y));
	_sprite->setScale((1.0f / _tex->getSize().x) * size.x, (1.0f / _tex->getSize().y) * size.y);
	_collision->setSize(sf::Vector2f(size.x, size.y));
	_collision->setOrigin(sf::Vector2f(size.x / 2.0f, size.y / 2.0f));
	_collision->setFillColor(sf::Color::Transparent);
	_collision->setOutlineColor(sf::Color::Green);
	_collision->setOutlineThickness(2.0f);
	_circleCollison = nullptr;
}

GraphicalBody::GraphicalBody(sf::Color color, sf::Vector2f position, sf::Vector2f size)
{
	_size = size;
	_tex = nullptr;
	_sprite = nullptr;
	_collision = nullptr;
	_circleCollison = nullptr;
	_noTexBody = new sf::RectangleShape(size);
	_noTexBody->setFillColor(color);
	_noTexBody->setOrigin(size.x / 2.0f, size.y / 2.0f);
	_noTexBody->setPosition(position);
}

GraphicalBody::GraphicalBody(std::string str, sf::Vector2f position,sf::Vector2f size, float radius)
{
	_tex = new sf::Texture();
	_tex->loadFromFile(str);
	_sprite = new sf::Sprite(*_tex);
	_circleCollison = new sf::CircleShape();
	_sprite->setOrigin(_tex->getSize().x / 2.0f, _tex->getSize().y / 2.0f);
	_sprite->setPosition(sf::Vector2f(position.x, position.y));
	_sprite->setScale((1.0f / _tex->getSize().x) * size.x, (1.0f / _tex->getSize().y) * size.y);
	_circleCollison->setRadius(radius/2);
	_circleCollison->setOrigin(size.x/2,size.y/2);
	_circleCollison->setFillColor(sf::Color::Transparent);
	_circleCollison->setOutlineColor(sf::Color::Green);
	_circleCollison->setOutlineThickness(2.0f);

	_collision = nullptr;
}

GraphicalBody::~GraphicalBody()
{
	delete _collision;
	delete _sprite;
	delete _tex;
	delete _circleCollison;
	delete _noTexBody;
}

void GraphicalBody::setPosition(sf::Vector2f pos)
{
	if(_sprite)
		_sprite->setPosition(pos);
	if(_collision)
		_collision->setPosition(pos);
	if (_circleCollison)
		_circleCollison->setPosition(pos);
	if (_noTexBody)
		_noTexBody->setPosition(pos);
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
	if(_sprite)
		_sprite->setRotation(angle);
	if(_collision)
		_collision->setRotation(angle);
	if (_circleCollison)
		_circleCollison->setRotation(angle);
	if (_noTexBody)
		_noTexBody->setRotation(angle);
}

void GraphicalBody::draw(sf::RenderWindow& win)
{
	if(_sprite)
		win.draw(*_sprite);
	if (_noTexBody)
		win.draw(*_noTexBody);
	//if(_collision)
		//win.draw(*_collision);
	//if (_circleCollison)
		//win.draw(*_circleCollison);
}

