#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Angry birds");
    Game* game = new Game();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}