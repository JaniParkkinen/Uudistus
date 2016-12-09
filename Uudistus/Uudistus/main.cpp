#include <SFML\Graphics.hpp>
#include <World.h>

#include "LobbyScene.h"
#include "SceneManager.h"
#include "NetworkManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Galactic Uudistus");
    window.setFramerateLimit(60);

    sf::Clock clock;

    SceneManager sm(&window);

    printf_s("Starting game loop\n");
    sm.changeScene(0);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		sm.update(clock.restart().asSeconds());
        window.clear();

		sm.draw(&window);

        window.display();
    }
    return 0;
}