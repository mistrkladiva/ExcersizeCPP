#include "Structs.h" // Ujistit se, že je zahrnutá definice Layer
#include <iostream>
#include "Player.h"
#include "MapGenerator.h"
#include "Npc.h"

int main()
{
    if (MAP_DATA.layers.empty()) {
        std::cout << "Načítání mapy selhalo nebo mapa je prázdná." << std::endl;
        return 0;
    }

#pragma region Testování získání interaktivní item dlaždice a vložení dlaždice
    Tile& interactiveTile = get_interactive_item_tile("neco");
    if (interactiveTile.id != "-1") {
        interactiveTile.x = 5;
    }

    Tile newTile;
    newTile = {
        "33",
        2,
        7,
        Attributes{
            {"custom_collider", "59,110,20,5"},
            {"interactive", "barrel"}
        }
    };

    if (!insert_new_item_tile(newTile)) {
        std::cout << "Vkládání nové dlaždice selhalo." << std::endl;
    }
#pragma endregion

    sf::RenderWindow window(sf::VideoMode((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT), "Simple c++ dop-down game");
    window.clear(sf::Color::Black);
    window.setVerticalSyncEnabled(true);

     sf::View defaultView;
    defaultView.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

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

    Direction playerSpriteDirection = Direction::Down;
    sf::Vector2f playerDirection = { 0,0 };

    SpriteCharacter playerSprt;
	playerSprt = { "Hero", 4, 4, sf::FloatRect(0, 0, 100,100), sf::FloatRect(0, 0, 50,20) };
    Player player(&window, charactersSpritesheet, playerSprt);

    SpriteCharacter npc1Sprt;
    npc1Sprt = { "Npc1", 4, 4, sf::FloatRect(400.f, 0.f, 100.f,100.f), sf::FloatRect(0, 0, 50,20) };
    Npc npc1(&window, charactersSpritesheet, npc1Sprt, sf::Vector2i(4,3));

    std::vector<sf::Sprite*> charactersSprite;
    charactersSprite.push_back(&player.getCurrentFrame());
	charactersSprite.push_back(&npc1.getCurrentFrame());

    MapGenerator map01(&window, mapLevel01Spritesheet, MAP_DATA, charactersSprite);

    player.update((int)playerSpriteDirection, playerDirection);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

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
        }

        window.clear(sf::Color::Black);
        defaultView.setCenter(sf::Vector2f(player.m_playerPos));
        window.setView(defaultView);
        
		player.update((int)playerSpriteDirection, playerDirection);
        npc1.update();
        map01.drawMap();
        player.draw();
		//npc1.update();
		npc1.draw();

        window.display();
    }
}
