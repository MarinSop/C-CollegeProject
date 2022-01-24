#include "Level.h"

Level::Level(std::string loc, b2World* world, sf::RenderWindow* win, InputManager* input)
{
	_win = win;
	_backgroundTex = new sf::Texture();
	_backgroundTex->loadFromFile("Sprites/background.jpeg");
	_backgroundSprite = new sf::Sprite(*_backgroundTex);
	_backgroundSprite->setScale((1.0f / _backgroundTex->getSize().x) * win->getSize().x, (1.0f / _backgroundTex->getSize().y) * win->getSize().y);

	_menuTex = new sf::Texture();
	_menuTex->loadFromFile("Sprites/menu.png");
	_menuSprite = new sf::Sprite(*_menuTex);
	_menuSprite->setPosition(10.0f, 10.0f);
	_menuSprite->setScale((1.0f / _menuTex->getSize().x) * 50.0f, (1.0f / _menuTex->getSize().y) * 50.0f);
	_restartTex = new sf::Texture();
	_restartTex->loadFromFile("Sprites/restart.png");
	_restartSprite = new sf::Sprite(*_restartTex);
	_restartSprite->setPosition(_win->getSize().x - _restartTex->getSize().x/2.0f-10.0f, 10.0f);
	_restartSprite->setScale((1.0f / _restartTex->getSize().x) * 50.0f, (1.0f / _restartTex->getSize().y) * 50.0f);

	_world = world;
	_input = input;
	float backY = (((1244 * 100) / _backgroundTex->getSize().y) * _win->getSize().y) / 100;
	_ground = new Entity(_world, _win,9999.0f, sf::Color::Green, b2_kinematicBody, b2Vec2(_win->getSize().x/2.0f, backY), b2Vec2(_win->getSize().x, 10.0f));
	_gameRes = sf::Vector2f(_win->getSize().x, _win->getSize().y);
	createLevel(loc);
}

Level::~Level()
{
	for (auto p : _woods)
	{
		delete p;
	}
	_woods.clear();
	for (auto p : _stones)
	{
		delete p;
	}
	_stones.clear();
	for (auto p : _pigs)
	{
		delete p;
	}
	_pigs.clear();
	delete _slingshot;
	delete _backgroundSprite;
	delete _backgroundTex;
	delete _ground;
	delete _restartTex;
	delete _restartSprite;
	delete _menuTex;
	delete _menuSprite;
}

void Level::createLevel(std::string str)
{
	TiXmlDocument doc(str.c_str());
	doc.LoadFile();
	TiXmlElement* root = doc.RootElement();
	if (root != NULL)
	{
		int resX;
		int resY;
		int tileX;
		int tileY;
		root->QueryIntAttribute("width", &resX);
		root->QueryIntAttribute("height", &resY);
		root->QueryIntAttribute("tilewidth", &tileX);
		root->QueryIntAttribute("tileheight", &tileY);
		_tiledRes = sf::Vector2f(resX * tileX, resY * tileY);
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
					x = (((x * 100.0f) / _tiledRes.x) * _gameRes.x) / 100.0f;
					y = (((y * 100.0f) / _tiledRes.y) * _gameRes.y) / 100.0f;
					b2Vec2 pos(x+width/2.0f, y + height / 2.0f);
					b2Vec2 size(width, height);
					if (objectGroupName == "wood")
					{
						Entity* entity = new Entity(_world, _win, woodHealth, "Sprites/wood.png", type, pos, size,"wood");
						_woods.push_back(entity);
					}
					else if (objectGroupName == "stone")
					{
						Entity* entity = new Entity(_world, _win, stoneHealth, "Sprites/stone.png", type, pos, size,"stone");
						_stones.push_back(entity);
					}
					else if (objectGroupName == "slingshot")
					{
						_slingshot = new Slingshot(_win,_input,_world, "Sprite/slingshot.png",sf::Vector2f(pos.x,pos.y),sf::Vector2f(size.x,size.y));
					}
					else if (objectGroupName == "pig")
					{
						Entity* entity = new Entity(_world, _win, pigHealth, "Sprites/pig.png", type, pos,size, size.x,"pig");
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
	handleDead();
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
	_win->draw(*_restartSprite);
	_win->draw(*_menuSprite);
}

bool Level::isGameWon()
{
	return _pigs.empty();
}

bool Level::isGameLost()
{
	if (_slingshot->areBirdsUsed())
	{
		if (currLostTimer > 0)
			currLostTimer -= 1.0f / 60.0f;
		else
			return 1;
	}
	return 0;
}

bool Level::isRestartClicked()
{
	if (_input->isMouseButtonDown(sf::Mouse::Left) && sf::Mouse::getPosition(*_win).x > _restartSprite->getPosition().x
		&& sf::Mouse::getPosition(*_win).x < _restartSprite->getPosition().x + _restartTex->getSize().x
		&& sf::Mouse::getPosition(*_win).y > _restartSprite->getPosition().y
		&& sf::Mouse::getPosition(*_win).y < _restartSprite->getPosition().y + _restartTex->getSize().y)
	{
		return true;
	}
	return false;
}

bool Level::isMenuClicked()
{
	if (_input->isMouseButtonDown(sf::Mouse::Left) && sf::Mouse::getPosition(*_win).x > _menuSprite->getPosition().x
		&& sf::Mouse::getPosition(*_win).x < _menuSprite->getPosition().x + _menuTex->getSize().x
		&& sf::Mouse::getPosition(*_win).y > _menuSprite->getPosition().y
		&& sf::Mouse::getPosition(*_win).y < _menuSprite->getPosition().y + _menuTex->getSize().y)
	{
		return true;
	}
	return false;
}

void Level::handleDead()
{
	_woods.erase(
		std::remove_if(
			_woods.begin(),
			_woods.end(),
			[](Entity* e) { return e->isDead();}
		),
		_woods.end()
	);
	_stones.erase(
		std::remove_if(
			_stones.begin(),
			_stones.end(),
			[](Entity* e) { return e->isDead(); }
		),
		_stones.end()
	);
	_pigs.erase(
		std::remove_if(
			_pigs.begin(),
			_pigs.end(),
			[](Entity* e) { return e->isDead(); }
		),
		_pigs.end()
	);
}
