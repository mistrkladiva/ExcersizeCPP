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
	if (!charactersSpritesheet.loadFromFile("assets/characters.png")) {
		std::cerr << "Error loading character spritesheet!" << std::endl;
        return 0;
    }

	DialogueManager gameDialogue(&window);

	GameEventsManager gameEventsManager(gameDialogue);

    Direction playerSpriteDirection = Direction::Down;
    sf::Vector2f playerDirection = { 0,0 };

    SpriteCharacter playerSprt;
	playerSprt = { "Hero", 6, 4, sf::FloatRect(0, 0, 100,100), sf::FloatRect(0.f, 0.f, 50.f, 20.f) };
    Player player(&window, gameEventsManager, charactersSpritesheet, playerSprt);

    SpriteCharacter anna;
    anna = { "Anna", 6, 4, sf::FloatRect(400.f, 0.f, 100.f,100.f), sf::FloatRect(-25.f, 30.f, 50.f, 20.f) };
    Npc npc1(&window, charactersSpritesheet, anna, sf::Vector2i(4,3));

    SpriteCharacter starosta;
    starosta = { "Starosta", 6, 4, sf::FloatRect(0.f, 600.f, 100.f,100.f), sf::FloatRect(-40.f, 30.f, 80.f, 20.f) };
    Npc npc2(&window, charactersSpritesheet, starosta, sf::Vector2i(11, 9));

    std::vector<sf::Sprite*> charactersSprite;
    charactersSprite.push_back(&player.getCurrentFrame());
	charactersSprite.push_back(&npc1.getCurrentFrame());
    charactersSprite.push_back(&npc2.getCurrentFrame());

    MapGenerator map01(&window, mapLevel01Spritesheet, MAP_DATA, charactersSprite);

    player.update((int)playerSpriteDirection, playerDirection);

	std::cout << "Player bounding box: " << player.getCurrentFrame().getGlobalBounds().left << ", "
        << player.getCurrentFrame().getGlobalBounds().top << ", "
        << player.getCurrentFrame().getGlobalBounds().width << ", "
        << player.getCurrentFrame().getGlobalBounds().height << std::endl;


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
        
        if (!gameDialogue.isDialogueActive()) {
            player.update((int)playerSpriteDirection, playerDirection);
        }
        else {
            // pokud je dialog aktivní, zastav pohyb hráče
            player.update((int)Direction::dialogue, sf::Vector2f{ 0,0 });
        }
		
        npc1.update();
		npc2.update();
        map01.drawMap();
        player.draw();
		// vykresluje jen kolizní obdélník
		npc1.draw();
		npc2.draw();
		gameDialogue.setDialoguePosition(sf::Vector2f(player.m_playerPos.x, player.m_playerPos.y - 100.f));
		gameDialogue.draw();
        window.display();
    }
}
