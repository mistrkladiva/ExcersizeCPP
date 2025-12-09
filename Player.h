#pragma once
#include <iostream>
#include "Structs.h"
#include "Globals.h"
#include "DialogueManager.h"
#include "GameEventsManager.h"

class Player
{
public:

	int direction; // idle=0, left=1, right=2, up=3, down=4
	// TODO: vypočítat souřadnice podle gridu mapy
	sf::Vector2f m_playerPos;
	Player(sf::RenderWindow* window, GameEventsManager& gameEventsManager, sf::Texture& spritesheet, SpriteCharacter sprt);

	void update(int direction, sf::Vector2f deltaPos);
	void draw();
	
	sf::Sprite& getCurrentFrame();

private:
    sf::RenderWindow* m_window;
    sf::Texture& m_spritesheet;
	SpriteCharacter m_sprt; // definice výřezu ve spritesheetu

	std::vector<std::vector<sf::Sprite>> m_frames;
	
	sf::Sprite m_currentFrame;
	int m_currentFrameIndex = 0;

	// timing for animation
	sf::Clock m_clock;
	sf::Time m_timeAccumulator = sf::Time::Zero;
	float m_frameDuration = 0.10f; // seconds per frame, nastavte podle potřeby
	int m_lastDirection = -2; // pomocné pro zjištění změny směru

	float m_playerSpeed = 3;

	sf::Vector2i m_collidedTilePos;

	GameEventsManager m_gameEventsManager;

	sf::Vector2i m_lastColliderTile = sf::Vector2i(-1, -1);
	
	bool m_isDialogueActive = false;

    void loadCharacterSprites();
	void animation(int direction);
	void move(sf::Vector2f deltaPos);
	bool isCollision(sf::Vector2f& playerPos);
	sf::Vector2f getNpcPosInTileGrid(sf::Vector2i gridPos);
};

