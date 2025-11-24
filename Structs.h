#pragma once
#include <SFML/Graphics.hpp>
static class Structs
{
	public:
		struct Character
		{
			int health;
			int mana;
			int strength;
			int agility;
			int intelligence;
		};

		struct sprtCharacter {
			std::string name;
			int frameRow = 0;
			int frameCol = 0;
			sf::IntRect textureArea;
		};
};

