#pragma once
#include "Structs.h"
#include "Globals.h"

class Player
{
public:

	int direction; // idle=0, left=1, right=2, up=3, down=4
	Player(sf::RenderWindow* window, sf::Texture& spritesheet, SpriteCharacter sprt);

	void update(int direction, sf::Vector2f deltaPos);
	void draw();
	

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

	

	// souøadnice pro pohyb
	sf::Vector2f m_playerPos = {500.f, 500.f};
	float m_playerSpeed = 0.1f;


    void loadCharacterSprites();
	void animation(int direction);
	void move(sf::Vector2f deltaPos);
};

