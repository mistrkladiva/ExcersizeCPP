
#include <iostream>
#include "Player.h"
#include "MapJsonParse.h"

int main()
{
    MapData loaded_map = MapJsonParse::LoadMapFromJsonFile("assets/map.json");

    if (loaded_map.layers.empty()) {
        std::cout << "Načítání mapy selhalo nebo mapa je prázdná." << std::endl;
        return 0;
    }

    Direction playerSpriteDirection = Direction::Down;
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
    player.update((int)playerSpriteDirection, playerDirection);
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
        playerSpriteDirection = Direction::Idle;
        playerDirection = { 0,0 };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerSpriteDirection = Direction::Left;
            playerDirection.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerSpriteDirection = Direction::Right;
            playerDirection.x = 1;
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerSpriteDirection = Direction::Up;
            playerDirection.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerSpriteDirection = Direction::Down;
            playerDirection.y = 1;
        }

        window.clear(sf::Color::Black);
		player.update((int)playerSpriteDirection, playerDirection);
		player.draw();

        window.display();
    }
}
