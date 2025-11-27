
#include <iostream>
#include "Player.h"
#include "MapJsonParse.h"
#include "MapGenerator.h"

int main()
{
    MapData loaded_map = MapJsonParse::LoadMapFromJsonFile("assets/map-level-01.json");

    if (loaded_map.layers.empty()) {
        std::cout << "Načítání mapy selhalo nebo mapa je prázdná." << std::endl;
        return 0;
    }

    sf::RenderWindow window(sf::VideoMode((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT), "Simple c++ dop-down game");
    window.clear(sf::Color::Black);

    window.setVerticalSyncEnabled(true);


    sf::View view2;
    view2.reset(sf::FloatRect(0, 0, 1024, 768));

    //view2.move(0, -500);

    sf::Texture mapLevel01Spritesheet;
    if (!mapLevel01Spritesheet.loadFromFile("assets/map-level-01.png")) {
        std::cerr << "Error loading character spritesheet!" << std::endl;
        return 0;
    }

    sf::Texture charactersSpritesheet;
	if (!charactersSpritesheet.loadFromFile("assets/characters2.png")) {
		std::cerr << "Error loading character spritesheet!" << std::endl;
        return 0;
    }

	MapGenerator map01(&window, mapLevel01Spritesheet, loaded_map);
    

    Direction playerSpriteDirection = Direction::Down;
    sf::Vector2f playerDirection = { 0,0 };
    SpriteCharacter playerSprt;
	playerSprt = { "Hero", 4, 4, sf::FloatRect(0, 0, 100,100) };

	Player player(&window, charactersSpritesheet, playerSprt);
    player.update((int)playerSpriteDirection, playerDirection);
    player.draw();

	sf::RectangleShape colliderRect;
	colliderRect.setSize(sf::Vector2f(100.f, 100.f));
	colliderRect.setPosition(100.f, 100.f);

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
        view2.setCenter(sf::Vector2f(player.m_playerPos));
        window.setView(view2);
        map01.drawMap();
		player.update((int)playerSpriteDirection, playerDirection);
		player.draw();
        window.draw(colliderRect);

        window.display();
    }
}
