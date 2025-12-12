#include "Structs.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include "AudioManager.h"
#include "Player.h"
#include "MapGenerator.h"
#include "Npc.h"

int main()
{
    if (MAP_DATA.layers.empty()) {
        std::cout << "Načítání mapy selhalo nebo mapa je prázdná." << std::endl;
        return 0;
    }

	AudioManager audioManager;
	AudioData backgroundMusicData = { "background-music", "assets/audio/background-music.ogg" };
    if (!audioManager.playMusic(backgroundMusicData)) {
		return 1;
    }

    std::vector<AudioData> dialogues = {
        { "starosta-1", "assets/audio/dialogues/starosta-1.mp3" },
        { "starosta-2", "assets/audio/dialogues/starosta-2.mp3" },
        { "starosta-end", "assets/audio/dialogues/starosta-end.mp3" },
        { "narrator-1", "assets/audio/dialogues/narrator-1.mp3" },
        { "narrator-2", "assets/audio/dialogues/narrator-2.mp3" },
        { "narrator-3", "assets/audio/dialogues/narrator-3.mp3" },
        { "narrator-4", "assets/audio/dialogues/narrator-4.mp3" },
        { "anna-1", "assets/audio/dialogues/anna-1.mp3" },
        { "helga-1", "assets/audio/dialogues/helga-1.mp3" },
        { "helga-2", "assets/audio/dialogues/helga-2.mp3" },
        { "rnd-anna-1", "assets/audio/dialogues/rnd-anna-1.mp3" },
        { "rnd-anna-2", "assets/audio/dialogues/rnd-anna-2.mp3" },
        { "rnd-anna-3", "assets/audio/dialogues/rnd-anna-3.mp3" },
        { "rnd-barrel-1", "assets/audio/dialogues/rnd-barrel-1.mp3" },
        { "rnd-barrel-2", "assets/audio/dialogues/rnd-barrel-2.mp3" },
        { "rnd-barrel-3", "assets/audio/dialogues/rnd-barrel-3.mp3" },
        { "rnd-bench-1", "assets/audio/dialogues/rnd-bench-1.mp3" },
        { "rnd-bench-2", "assets/audio/dialogues/rnd-bench-2.mp3" },
        { "rnd-bench-3", "assets/audio/dialogues/rnd-bench-3.mp3" },
        { "rnd-helga-1", "assets/audio/dialogues/rnd-helga-1.mp3" },
        { "rnd-helga-2", "assets/audio/dialogues/rnd-helga-2.mp3" },
		{ "rnd-helga-3", "assets/audio/dialogues/rnd-helga-3.mp3" },
        { "rnd-starosta-1", "assets/audio/dialogues/rnd-starosta-1.mp3" },
        { "rnd-starosta-2", "assets/audio/dialogues/rnd-starosta-2.mp3" },
        { "rnd-starosta-3", "assets/audio/dialogues/rnd-starosta-3.mp3" },
    };

    for (auto& dialogue : dialogues) {
        audioManager.loadSound(dialogue);
    }

	//audioManager.playDialogueSound("dialogue-2");

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
            {"interactive", "Barrel"}
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

    sf::Texture titleImage;
    if (!titleImage.loadFromFile("assets/title-image.png")) {
        std::cerr << "Error loading title image!" << std::endl;
        return 0;
    }

	// vykreslení úvodního obrázku
	sf::Sprite titleSprite;
	titleSprite.setTexture(titleImage);
    window.draw(titleSprite);
	window.display();

    // čekání na stisk klávesy pro start hry
    sf::Event event;
    bool startGame = false;

    while (!startGame)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return 0;

            if (event.type == sf::Event::KeyPressed)
                startGame = true;
        }
    }

    sf::Texture mapLevel01Spritesheet;
    if (!mapLevel01Spritesheet.loadFromFile("assets/map-level-01.png")) {
        std::cerr << "Error loading maplevel-01 spritesheet!" << std::endl;
        return 0;
    }

    sf::Texture charactersSpritesheet;
	if (!charactersSpritesheet.loadFromFile("assets/characters.png")) {
		std::cerr << "Error loading character spritesheet!" << std::endl;
        return 0;
    }

	DialogueManager gameDialogue(&window);

	GameEventsManager gameEventsManager(gameDialogue, audioManager);

    Direction playerSpriteDirection = Direction::Idle;
    sf::Vector2f playerDirection = { 0,0 };

    SpriteCharacter playerSprt;
	playerSprt = { "Hero", 6, 4, sf::FloatRect(0, 0, 100,100), sf::FloatRect(0.f, 0.f, 50.f, 20.f) };
    Player player(&window, gameEventsManager, charactersSpritesheet, playerSprt);

    SpriteCharacter anna;
    anna = { "Anna", 6, 4, sf::FloatRect(400.f, 0.f, 100.f,100.f), sf::FloatRect(-25.f, 30.f, 50.f, 20.f) };
    Npc npc1(&window, charactersSpritesheet, anna, sf::Vector2i(12,5));

    SpriteCharacter helga;
    helga = { "Helga", 6, 4, sf::FloatRect(400.f, 600.f, 100.f,100.f), sf::FloatRect(-25.f, 30.f, 50.f, 20.f) };
    Npc npc3(&window, charactersSpritesheet, helga, sf::Vector2i(22, 9));

    SpriteCharacter starosta;
    starosta = { "Starosta", 6, 4, sf::FloatRect(0.f, 600.f, 100.f,100.f), sf::FloatRect(-40.f, 30.f, 80.f, 20.f) };
    Npc npc2(&window, charactersSpritesheet, starosta, sf::Vector2i(16, 13));

    std::vector<sf::Sprite*> charactersSprite;
    charactersSprite.push_back(&player.getCurrentFrame());
	charactersSprite.push_back(&npc1.getCurrentFrame());
    charactersSprite.push_back(&npc2.getCurrentFrame());
    charactersSprite.push_back(&npc3.getCurrentFrame());

    MapGenerator map01(&window, mapLevel01Spritesheet, MAP_DATA, charactersSprite);

	

    // startovní dialog ve hře
	float dialogueDuration = audioManager.getSoundDuration("narrator-1");
	audioManager.playDialogueSound("narrator-1");
	gameDialogue.setDialogueMessage("To je dneska zase den,\nmám pocit, že se tu něco bude dít.", dialogueDuration);

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
        
        if (!gameDialogue.isDialogueActive()) {
            player.update((int)playerSpriteDirection, playerDirection);
        }
        else {
            // pokud je dialog aktivní, zastav pohyb hráče
            player.update((int)Direction::dialogue, sf::Vector2f{ 0,0 });
        }
		
        npc1.update();
		npc2.update();
        npc3.update();
        map01.drawMap();
        player.draw();
		// vykresluje jen kolizní obdélník
		npc1.draw();
		npc2.draw();
        npc3.draw();
		gameDialogue.setDialoguePosition(sf::Vector2f(player.m_playerPos.x, player.m_playerPos.y - 100.f));
		gameDialogue.draw();
        window.display();
    }
}
