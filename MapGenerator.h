#pragma once
#include <iostream>
#include "Structs.h"
#include "Globals.h"
class MapGenerator
{
public:
	MapGenerator(sf::RenderWindow* window, sf::Texture& mapSpritesheet, MapData& mapData);
	void drawMap();

private:
	sf::RenderWindow* m_window;
	sf::Texture& m_mapSpritesheet;
	MapData& m_mapData;
	std::vector<sf::Sprite> m_tiles;

	std::vector<sf::Sprite> m_mapSprites;
	void loadTiles();

	
};

