#include "Game.h"
#include "SFML/Graphics.hpp"

Game::Game(b2World* world, sf::RenderWindow* win)
{
	_win = win;
	_world = world;
	_input = new InputManager();
	_mainMenu = new MainMenu(_win,_input,lvlNum);
	
}

Game::~Game()
{
	delete _currentLevel;
	delete _input;
	delete _mainMenu;
}

void Game::update()
{
	if (_mainMenu)
	{
		lvlGoRight();
		lvlGoLeft();
		play();
	}
	if (_currentLevel)
	{
		_currentLevel->update();
		gameWon();
		restartLevel();
		gameLost();
		goToMainMenu();
	}
}

void Game::draw()
{
	if(_mainMenu)
		_mainMenu->draw();
	if(_currentLevel)
		_currentLevel->draw();
}

void Game::play()
{
	if (_mainMenu->isPlayClicked())
	{
		std::string lvlLoc = "Levels/level" + std::to_string(lvlNum) + ".tmx";
		_currentLevel = new Level(lvlLoc, _world, _win, _input);
		delete _mainMenu;
		_mainMenu = nullptr;
	}
}

bool Game::exit()
{
	if (_mainMenu)
	{
		if (_mainMenu->isExitClicked())
		{
			return true;
		}
	}
	return false;
}

void Game::lvlGoLeft()
{
	if (_mainMenu->isLeftClicked())
	{
		lvlNum -= 1;
		if (lvlNum < 1)
			lvlNum = 1;
	}
}

void Game::lvlGoRight()
{
	if (_mainMenu->isRightClicked())
	{
		lvlNum += 1;
		if (lvlNum > 5)
			lvlNum = 5;
	}
}

void Game::gameWon()
{
	if (_currentLevel->isGameWon())
	{
		if (currentWonTimer <= 0)
		{
			lvlNum += 1;
			if (lvlNum > 5)
				lvlNum = 5;
			loadLvl(lvlNum);
			currentWonTimer = wonTimer;
		}
		else
			currentWonTimer -= 1.0f / 60.0f;
	}
}

void Game::loadLvl(int lvl)
{
	delete _currentLevel;
	std::string lvlLoc = "levels/level" + std::to_string(lvlNum) + ".tmx";
	_currentLevel = new Level(lvlLoc, _world, _win, _input);
}

void Game::gameLost()
{
	if (_currentLevel->isGameLost())
		loadLvl(lvlNum);
}

void Game::restartLevel()
{
	if (_currentLevel->isRestartClicked())
	{
		delete _currentLevel;
		std::string lvlLoc = "levels/level" + std::to_string(lvlNum) + ".tmx";
		_currentLevel = new Level(lvlLoc, _world, _win, _input);
	}
}

void Game::goToMainMenu()
{
	if (_currentLevel->isMenuClicked())
	{
		delete _currentLevel;
		_currentLevel = nullptr;
		_mainMenu = new MainMenu(_win, _input,lvlNum);
	}
}

