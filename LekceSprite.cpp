
#include <iostream>
#include "Player.h"
#include "MapGenerator.h"
#include "DialogueManager.h"

int main()
{
    //MapData loaded_map = MapJsonParse::LoadMapFromJsonFile("assets/map-level-01.json");
    //MAP_DATA = MapJsonParse::LoadMapFromJsonFile("assets/map-level-01.json");

    if (MAP_DATA.layers.empty()) {
        std::cout << "Načítání mapy selhalo nebo mapa je prázdná." << std::endl;
        return 0;
    }

    sf::RenderWindow window(sf::VideoMode((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT), "Simple c++ dop-down game");
    window.clear(sf::Color::Black);
    window.setVerticalSyncEnabled(true);


    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
    }

    text.setFont(font);

    // set the string to display
    text.setString("message");

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold);
    text.setPosition(100.f, 100.f);

    





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
	playerSprt = { "Hero", 4, 4, sf::FloatRect(0, 0, 100,100) };

   
    //DialogueManager dialogue(&window);

	Player player(&window, charactersSpritesheet, playerSprt);

    MapGenerator map01(&window, mapLevel01Spritesheet, MAP_DATA, player.getCurrentFrame());

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
        map01.drawMap();
        player.draw();

        window.display();
    }
}
