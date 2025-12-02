#pragma once
#include <iostream>
#include "Structs.h"
#include "Globals.h"
#include "DialogueManager.h"

class Player
{
public:

	int direction; // idle=0, left=1, right=2, up=3, down=4
	sf::Vector2f m_playerPos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	Player(sf::RenderWindow* window, sf::Texture& spritesheet, SpriteCharacter sprt);

	void update(int direction, sf::Vector2f deltaPos);
	void draw();
	
	sf::Sprite& getCurrentFrame();

private:
    sf::RenderWindow* m_window;
    sf::Texture& m_spritesheet;
	SpriteCharacter m_sprt; // definice výøezu ve spritesheetu

	std::vector<std::vector<sf::Sprite>> m_frames;
	
	sf::Sprite m_currentFrame;
	int m_currentFrameIndex = 0;

	// timing for animation
	sf::Clock m_clock;
	sf::Time m_timeAccumulator = sf::Time::Zero;
	float m_frameDuration = 0.10f; // seconds per frame, nastavte podle potøeby
	int m_lastDirection = -2; // pomocné pro zjištìní zmìny smìru

	float m_playerSpeed = 3;

	sf::Vector2i m_collidedTilePos;

	DialogueManager m_dialogue;
	
	bool m_isDialogueActive = false;

    void loadCharacterSprites();
	void animation(int direction);
	void move(sf::Vector2f deltaPos);
	bool isCollision(sf::Vector2f& playerPos);
};

