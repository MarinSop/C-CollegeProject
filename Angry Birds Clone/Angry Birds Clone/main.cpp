#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Game.h"
#include "Entity.h"
#include "Level.h"
#include "Slingshot.h"
#include "InputManager.h"
#define SCALE 30.0f

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024,768), "Angry birds");
    window.setFramerateLimit(60);
    Game* game = new Game();
    b2Vec2 gravity(0.0f, 9.81f);
    b2World world(gravity);

    InputManager input;
    Level lvl = Level("levels/level1.tmx",&world,&window,&input);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
        }
        world.Step(1 / 60.f, 8, 3);
        window.clear(sf::Color(69, 179, 224));
        lvl.update();
        lvl.draw();
        window.display();
    }

    return 0;
}