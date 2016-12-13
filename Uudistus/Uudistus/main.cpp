#include <SFML\Graphics.hpp>
#include <World.h>

#include "LobbyScene.h"
#include "SceneManager.h"
#include "NetworkManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Galactic Uudistus");
    window.setFramerateLimit(60);

    std::string str = "127.0.0.1";
    sf::Font font;
    font.loadFromFile("assets/font.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setFillColor(sf::Color::Green);
    text.setPosition(32, 32);

    //get ip
    bool enter = false;
    while (!enter && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // check the type of the event...
            switch (event.type)
            {
                // window closed
            case sf::Event::Closed:
                window.close();
                break;
                // key pressed
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Return)
                {
                    enter = true;
                }
                break;
            case sf::Event::TextEntered:
                {
                    // Handle ASCII characters only
                    if (event.text.unicode == '\b')
                    {
                        if(str.size() > 0)
                            str.erase(str.size() - 1, 1);
                    }
                    else if (event.text.unicode < 128)
                    {
                        str += static_cast<char>(event.text.unicode);
                    }
                    text.setString(str);
                }
                break;
                // we don't process other types of events
            default:
                break;
            }
        }
        window.clear();
        window.draw(text);
        window.display();
    }

    NetworkManager::instance()->initNetwork(str);

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