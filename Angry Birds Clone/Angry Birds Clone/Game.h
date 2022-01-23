#pragma once
#include "Level.h"
#include "MainMenu.h"
class Game
{
public:
	Game(b2World* world,sf::RenderWindow* win);
	~Game();
	
	void update();
	void draw();
	bool exit();

private:
	void play();
	void lvlGoLeft();
	void lvlGoRight();
	void gameWon();
	void loadLvl(int lvl);
	void gameLost();
	void restartLevel();
	void goToMainMenu();


	Level* _currentLevel;
	MainMenu* _mainMenu;
	sf::RenderWindow* _win;
	b2World* _world;
	InputManager* _input;
	int lvlNum = 1;

	float wonTimer = 3.0f;
	float currentWonTimer = wonTimer;
};

