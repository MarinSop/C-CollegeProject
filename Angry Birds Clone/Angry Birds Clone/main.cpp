#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Game.h"
#include "PhysicalBody.h"
#include "Bird.h"
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
    PhysicalBody* groundBody = new PhysicalBody(&world, b2_staticBody, b2Vec2(500.0f, 700.0f), b2Vec2(1024.0f, 10.0f));

    sf::RectangleShape ground(sf::Vector2f(1024.f, 10.f));
    ground.setOrigin(sf::Vector2f(1024.f / 2.0f, 10.f / 2.0f));
    ground.setFillColor(sf::Color::Red);
    ground.setPosition(sf::Vector2f(groundBody->getPositionScaled().x, groundBody->getPositionScaled().y));


    //Bird red = Bird(&window,"Sprites/red.png",&world, b2_dynamicBody, b2Vec2(400.0f, 300.0f), b2Vec2(32.0f, 32.0f));
    InputManager input;
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
        slingshot.update();
        slingshot.draw();
        //red.update();
        //red.draw();
        window.draw(ground);
        window.display();
    }

    return 0;
}