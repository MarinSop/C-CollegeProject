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

    Level lvl = Level("levels/level1.tmx",&world,&window);
    InputManager input;
    Entity ground = Entity(&world, &window, 100.0f, sf::Color::Yellow,b2_staticBody, b2Vec2(512.0f, 700.0f), b2Vec2(1024.0f, 10.0f));
    Slingshot slingshot = Slingshot(&window,&input,&world,"Sprite/slingshot.png",sf::Vector2f(100.0f,500.0f),sf::Vector2f(64,128));
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
        slingshot.update();
        lvl.draw();
        slingshot.draw();
        ground.draw();
       // window.draw(ground);
        window.display();
    }

    return 0;
}