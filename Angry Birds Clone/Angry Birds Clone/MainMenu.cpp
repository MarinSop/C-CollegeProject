#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* win, InputManager* input,int lvl)
{
	lvlNum = lvl;
	_win = win;
	_input = input;

	_backgroundTex = new sf::Texture();
	_backgroundTex->loadFromFile("Sprites/mainmenubackground.jpg");
	_backgroundSprite = new sf::Sprite(*_backgroundTex);
	_backgroundSprite->setScale((1.0f / _backgroundTex->getSize().x) * win->getSize().x, (1.0f / _backgroundTex->getSize().y) * win->getSize().y);

	_playTex = new sf::Texture();
	_playTex->loadFromFile("Sprites/play.png");
	_playSprite = new sf::Sprite(*_playTex);
	_playSprite->setPosition(_win->getSize().x *0.5f - _playTex->getSize().x*0.5f, _win->getSize().y *0.25f - _playTex->getSize().y * 0.5f);
	

	_exitTex = new sf::Texture();
	_exitTex->loadFromFile("Sprites/exit.png");
	_exitSprite = new sf::Sprite(*_exitTex);
	_exitSprite->setPosition(_win->getSize().x * 0.5f - _exitTex->getSize().x * 0.5f, _win->getSize().y * 0.75f - _exitTex->getSize().y * 0.5f);

	_rightTex = new sf::Texture();
	_rightTex->loadFromFile("Sprites/right.png");
	_rightSprite = new sf::Sprite(*_rightTex);
	_rightSprite->setPosition(_win->getSize().x * 0.7f - _rightTex->getSize().x * 0.5f, _win->getSize().y * 0.5f - _rightTex->getSize().x * 0.5f);

	_leftTex = new sf::Texture();
	_leftTex->loadFromFile("Sprites/left.png");
	_leftSprite = new sf::Sprite(*_leftTex);
	_leftSprite->setPosition(_win->getSize().x * 0.3f - _leftTex->getSize().x * 0.5f, _win->getSize().y * 0.5f - _leftTex->getSize().x * 0.5f);

	_textboxTex = new sf::Texture();
	_textboxTex->loadFromFile("Sprites/textbox.png");
	_textboxSprite = new sf::Sprite(*_textboxTex);
	_textboxSprite->setPosition(_win->getSize().x * 0.5f - _textboxTex->getSize().x * 0.5f, _win->getSize().y * 0.51f - _textboxTex->getSize().x * 0.5f);

	_font = new sf::Font();
	_font->loadFromFile("Roboto-Regular.ttf");

	_text = new sf::Text(std::to_string(lvlNum),*_font,30.0f);
	_text->setPosition(_textboxSprite->getPosition().x + _textboxTex->getSize().x*0.5f-15.0f, _textboxSprite->getPosition().y + _textboxTex->getSize().y*0.5f-15.0f);

}

MainMenu::~MainMenu()
{
	delete _backgroundTex;
	delete _backgroundSprite;
	delete _playTex;
	delete _playSprite;
	delete _exitTex;
	delete _exitSprite;
	delete _leftTex;
	delete _leftSprite;
	delete _rightTex;
	delete _rightSprite;
	delete _textboxTex;
	delete _textboxSprite;
	delete _text;
	delete _font;
}

bool MainMenu::isPlayClicked()
{
	if (_input->isMouseButtonDown(sf::Mouse::Left) && sf::Mouse::getPosition(*_win).x > _playSprite->getPosition().x
		&& sf::Mouse::getPosition(*_win).x < _playSprite->getPosition().x + _playTex->getSize().x
		&& sf::Mouse::getPosition(*_win).y > _playSprite->getPosition().y
		&& sf::Mouse::getPosition(*_win).y < _playSprite->getPosition().y + _playTex->getSize().y)
	{
		return true;
	}
	return false;
}

bool MainMenu::isExitClicked()
{
	if (_input->isMouseButtonDown(sf::Mouse::Left) && sf::Mouse::getPosition(*_win).x > _exitSprite->getPosition().x
		&& sf::Mouse::getPosition(*_win).x < _exitSprite->getPosition().x + _exitTex->getSize().x
		&& sf::Mouse::getPosition(*_win).y > _exitSprite->getPosition().y
		&& sf::Mouse::getPosition(*_win).y < _exitSprite->getPosition().y + _exitTex->getSize().y)
	{
		return true;
	}
	return false;
}

bool MainMenu::isRightClicked()
{
	if (_input->isMouseButtonDownOnce(sf::Mouse::Left) && sf::Mouse::getPosition(*_win).x > _rightSprite->getPosition().x
		&& sf::Mouse::getPosition(*_win).x < _rightSprite->getPosition().x + _rightTex->getSize().x
		&& sf::Mouse::getPosition(*_win).y > _rightSprite->getPosition().y
		&& sf::Mouse::getPosition(*_win).y < _rightSprite->getPosition().y + _rightTex->getSize().y)
	{
		lvlNum += 1;
		if (lvlNum > 5)
			lvlNum = 5;
		_text->setString(std::to_string(lvlNum));
		return true;
	}
	return false;
}

bool MainMenu::isLeftClicked()
{
	if (_input->isMouseButtonDownOnceSecond(sf::Mouse::Left) && sf::Mouse::getPosition(*_win).x > _leftSprite->getPosition().x
		&& sf::Mouse::getPosition(*_win).x < _leftSprite->getPosition().x + _leftTex->getSize().x
		&& sf::Mouse::getPosition(*_win).y > _leftSprite->getPosition().y
		&& sf::Mouse::getPosition(*_win).y < _leftSprite->getPosition().y + _leftTex->getSize().y)
	{
		lvlNum -= 1;
		if (lvlNum < 1)
			lvlNum = 1;
		_text->setString(std::to_string(lvlNum));
		return true;
	}
	return false;
}

void MainMenu::draw()
{
	_win->draw(*_backgroundSprite);
	_win->draw(*_playSprite);
	_win->draw(*_exitSprite);
	_win->draw(*_leftSprite);
	_win->draw(*_rightSprite);
	_win->draw(*_textboxSprite);
	_win->draw(*_text);
}
