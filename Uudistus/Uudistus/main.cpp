#include <SFML\Graphics.hpp>

#include "GameScene.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Galactic Uudistus");

    window.setFramerateLimit(60);

    sf::CircleShape shape(256.f);
    shape.setFillColor(sf::Color(0, 25, 10));

    Scene* current = new GameScene(&window);

    printf_s("Starting game loop\n");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        current->update(0.1f);

        window.clear();

        current->render(&window);
        //window.draw(shape);
        window.display();
    }
    return 0;
}