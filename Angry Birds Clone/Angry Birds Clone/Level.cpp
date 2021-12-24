#include "Level.h"

Level::Level(std::string loc, b2World* world, sf::RenderWindow* win)
{
	_win = win;
	_world = world;
	createLevel(loc);
}

Level::~Level()
{
}

void Level::createLevel(std::string str)
{
	TiXmlDocument doc(str.c_str());
	doc.LoadFile();
	TiXmlElement* root = doc.RootElement();
	if (root != NULL)
	{
		TiXmlElement* objectGroup = root->FirstChildElement("objectgroup");
		if (objectGroup)
		{
			while (objectGroup)
			{
				TiXmlElement* object = objectGroup->FirstChildElement("object");
				std::string objectGroupName = objectGroup->Attribute("name");
				while (object)
				{
					b2BodyType type;
					std::string typeStr = object->Attribute("type");
					if (typeStr == "dynamic")
						type = b2_dynamicBody;
					else
						type = b2_staticBody;
					float x;
					float y;
					float width;
					float height;
					object->QueryFloatAttribute("x", &x);
					object->QueryFloatAttribute("y", &y);
					object->QueryFloatAttribute("width", &width);
					object->QueryFloatAttribute("height", &height);
					b2Vec2 pos(x+width/2, y+height/2);
					b2Vec2 size(width, height);
					if (objectGroupName == "wood")
					{
						Entity* entity = new Entity(_world, _win, woodHealth, sf::Color::Yellow, type, pos, size);
						_woods.push_back(entity);
					}
					else if (objectGroupName == "stone")
					{
						Entity* entity = new Entity(_world, _win, stoneHealth, sf::Color::Blue, type, pos, size);
						_stones.push_back(entity);
					}
					object = object->NextSiblingElement("object");
			std::cout << type << " " << x << " " << y << " " << width << " " << height << std::endl;
				}
				objectGroup = objectGroup->NextSiblingElement("objectgroup");
			}
		}
	}
}

void Level::update()
{
	int woodSize = _woods.size();
	for (int i = 0; i < woodSize; i++)
	{
		_woods[i]->update();
	}
	int stoneSize = _stones.size();
	for (int i = 0; i < stoneSize; i++)
	{
		_stones[i]->update();
	}
}

void Level::draw()
{
	int woodSize = _woods.size();
	for (int i = 0; i < woodSize; i++)
	{
		_woods[i]->draw();
	}
	int stoneSize = _stones.size();
	for (int i = 0; i < stoneSize; i++)
	{
		_stones[i]->draw();
	}
}
