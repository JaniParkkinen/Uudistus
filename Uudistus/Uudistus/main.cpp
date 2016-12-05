#include <SFML\Graphics.hpp>
#include <World.h>

#include "LobbyScene.h"
#include "SceneManager.h"
#include "NetworkManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Galactic Uudistus");
    window.setFramerateLimit(60);

    sf::CircleShape shape(256.f);
    shape.setFillColor(sf::Color(0, 25, 10));

	//Scene* lobby = new LobbyScene(&window);
    //Scene* current = new GameScene(&window);
	SceneManager sm;
	
    printf_s("Starting game loop\n");
	sm.changeScene(new LobbyScene(&window, &sm));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		//lobby->update(0.1f);
		//current->update(0.1f);

		sm.update(0.1f);
        window.clear();

		sm.draw(&window);
		//lobby->draw(&window);
		//current->draw(&window);
		//window.draw(shape);
        window.display();
    }
    return 0;
}