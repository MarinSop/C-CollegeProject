#pragma once
#include <SFML/Graphics.hpp>
class GraphicalBody
{
public:
	GraphicalBody(std::string str,sf::Vector2f position, sf::Vector2f size);
	GraphicalBody(std::string str, sf::Vector2f position,sf::Vector2f size, float radius);
	~GraphicalBody();

	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void setRotation(float angle);
	void draw(sf::RenderWindow& win);
private:
	sf::Texture* _tex;
	sf::Sprite* _sprite;
	sf::RectangleShape* _collision;
	sf::CircleShape* _circleCollison;
	sf::Vector2f _size;
};

