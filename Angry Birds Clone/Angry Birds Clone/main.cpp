#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MyContactListener.h"
#define SCALE 30.0f

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280,800), "Angry birds");
    window.setFramerateLimit(60);
    b2Vec2 gravity(0.0f, 9.81f);
    b2World world(gravity);
    MyContactListener* myContactListener = new MyContactListener();
    world.SetContactListener(myContactListener);

    Game* game = new Game(&world,&window);
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
        game->update();
        game->draw();
        window.display();
        if (game->exit())
        {
            delete game;
            delete myContactListener;
            window.close();
        }
    }

    return 0;
}