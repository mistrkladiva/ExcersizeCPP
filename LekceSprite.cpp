
#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Structs.h"
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Simple c++ dop-down game");

    sf::Texture charactestSpritesheet;
	if (!charactestSpritesheet.loadFromFile("assets/characters.png")) {
		std::cerr << "Error loading character spritesheet!" << std::endl;
        return 0;
    }

    Structs::sprtCharacter playerSprt;
	playerSprt = { "Hero", 4, 3, sf::IntRect(0, 400, 100,100) };

	Player player(&window, charactestSpritesheet, playerSprt);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
		player.update(3); // idle
		player.draw();

        window.display();
    }
}
