
#include <iostream>
#include "Structs.h"
#include "Globals.h"
#include "Player.h"

int main()
{
	int playerSpriteDirection = 0; // idle= -1, down=0, right=1, up=2, left=3
    sf::Vector2f playerDirection = {0,0};

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simple c++ dop-down game");
    window.clear(sf::Color::Black);

    sf::Texture charactestSpritesheet;
	if (!charactestSpritesheet.loadFromFile("assets/characters2.png")) {
		std::cerr << "Error loading character spritesheet!" << std::endl;
        return 0;
    }

    SpriteCharacter playerSprt;
	playerSprt = { "Hero", 4, 4, sf::IntRect(0, 0, 100,100) };

	Player player(&window, charactestSpritesheet, playerSprt);
    player.update(playerSpriteDirection, playerDirection);
    player.draw();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // vstup z klávesnice
        playerSpriteDirection = -1;
        playerDirection = { 0,0 };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerSpriteDirection = 3;
            playerDirection.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerSpriteDirection = 1;
            playerDirection.x = 1;
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerSpriteDirection = 2;
            playerDirection.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerSpriteDirection = 0;
            playerDirection.y = 1;
        }

        window.clear(sf::Color::Black);
		player.update(playerSpriteDirection, playerDirection);
		player.draw();

        window.display();
    }
}
