#include "Level.h"

Level::Level(std::string loc, b2World* world, sf::RenderWindow* win, InputManager* input)
{
	_win = win;
	_backgroundTex = new sf::Texture();
	_backgroundTex->loadFromFile("Sprites/background.jpeg");
	_backgroundSprite = new sf::Sprite(*_backgroundTex);
	_backgroundSprite->setScale((1.0f / _backgroundTex->getSize().x) * win->getSize().x, (1.0f / _backgroundTex->getSize().y) * win->getSize().y);
	_world = world;
	_input = input;
	_ground = new Entity(_world, _win,9999.0f, sf::Color::Green, b2_staticBody, b2Vec2(_win->getSize().x/2.0f, 666), b2Vec2(_win->getSize().x, 10.0f));
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
						Entity* entity = new Entity(_world, _win, woodHealth, "Sprites/wood.png", type, pos, size);
						_woods.push_back(entity);
					}
					else if (objectGroupName == "stone")
					{
						Entity* entity = new Entity(_world, _win, stoneHealth, "Sprites/stone.png", type, pos, size);
						_stones.push_back(entity);
					}
					else if (objectGroupName == "slingshot")
					{
						_slingshot = new Slingshot(_win,_input,_world, "Sprite/slingshot.png",sf::Vector2f(pos.x,pos.y),sf::Vector2f(size.x,size.y));
					}
					else if (objectGroupName == "pig")
					{
						Entity* entity = new Entity(_world, _win, pigHealth, "Sprites/pig.png", type, pos,size, size.x);
						_pigs.push_back(entity);
					}
					object = object->NextSiblingElement("object");
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
	int pigSize = _pigs.size();
	for (int i = 0; i < pigSize; i++)
	{
		_pigs[i]->update();
	}
	_slingshot->update();
}

void Level::draw()
{
	_win->draw(*_backgroundSprite);
	//_ground->draw();
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
	int pigSize = _pigs.size();
	for (int i = 0; i < pigSize; i++)
	{
		_pigs[i]->draw();
	}
	_slingshot->draw();
}
