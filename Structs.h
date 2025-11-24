#pragma once
#include <SFML/Graphics.hpp>

struct Character
{
	int health;
	int mana;
	int strength;
	int agility;
	int intelligence;
};

struct SpriteCharacter {
	std::string name;
	int frameRow = 0;
	int frameCol = 0;
	sf::IntRect textureArea;
};