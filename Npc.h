#pragma once
#include <iostream>
#include "Structs.h"
#include "Globals.h"
#include "DialogueManager.h"
class Npc
{
public:
	int direction; // idle=0, left=1, right=2, up=3, down=4
	sf::Vector2f m_npcPos = { 600.f, 500.f};
	Npc(sf::RenderWindow* window, sf::Texture& spritesheet, SpriteCharacter& sprt, sf::Vector2i gridPos);

	void update();
	void draw();

	sf::Sprite& getCurrentFrame();

private:
	sf::RenderWindow* m_window;
	sf::Texture& m_spritesheet;
	SpriteCharacter m_sprt; // definice výřezu ve spritesheetu
	sf::Vector2i m_gridPos;

	std::vector<std::vector<sf::Sprite>> m_frames;

	sf::Sprite m_currentFrame;
	int m_currentFrameIndex = 0;

	// timing for animation
	sf::Clock m_clock;
	sf::Time m_timeAccumulator = sf::Time::Zero;
	float m_frameDuration = 0.3f; // seconds per frame, nastavte podle potřeby
	int m_lastDirection = -2; // pomocné pro zjištění změny směru

	float m_playerSpeed = 3;

	sf::Vector2i m_collidedTilePos;

	DialogueManager m_dialogue;

	sf::RectangleShape m_npcColliderShape;
	TileCollider m_tileCollider;

	bool m_isDialogueActive = false;

	void loadCharacterSprites();
	void animation(int direction);
	void move(sf::Vector2f deltaPos);
	bool isCollision(sf::Vector2f& playerPos);
	sf::Vector2f getNpcPosInTileGrid(sf::Vector2i& gridPos);
};

