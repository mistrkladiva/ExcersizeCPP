#pragma once
#include <iostream>
#include <vector>
#include "Structs.h"
class Player
{
public:

	int direction; // idle=0, left=1, right=2, up=3, down=4
	Player(sf::RenderWindow* window, sf::Texture& spritesheet, Structs::sprtCharacter& sprt);

	void update(int direction);
	void draw();
	void move(int x, int y);

private:
    sf::RenderWindow* m_window;
    sf::Texture m_spritesheet;
    Structs::sprtCharacter m_sprt;

    sf::Sprite m_sprite;
    std::vector<sf::Sprite> m_animation;

	sf::Sprite m_currentFrame;
	int m_currentFrameIndex = 0;
	std::vector<sf::Sprite> m_currentAnimationRow;

	// timing for animation
	sf::Clock m_clock;
	sf::Time m_timeAccumulator = sf::Time::Zero;
	float m_frameDuration = 0.15f; // seconds per frame, nastavte podle potøeby

	int m_lastDirection = -2; // pomocné pro zjištìní zmìny smìru

	
    void loadCharacterSprites();
	void animation();
};

