#pragma once
#include <iostream>
#include "Structs.h"
#include "Globals.h"

class MapGenerator
{
public:
    MapGenerator(sf::RenderWindow* window, sf::Texture& mapSpritesheet, MapData& mapData, sf::Sprite& playerSprite);
    void drawMap();

private:
    sf::RenderWindow* m_window;
    sf::Texture& m_mapSpritesheet;
    MapData& m_mapData;

    std::vector<sf::Sprite> m_tiles;
    std::vector<sf::Sprite> m_mapSprites;
    std::vector<sf::Sprite> m_topLayer;

    // HLAVNÍ ZMÌNA: ukazatele, ne kopie
    std::vector<sf::Sprite*> m_overlappingLayer;

    sf::Sprite& m_playerSprite;

    void loadTiles();
    sf::FloatRect parseColliderString(const std::string& colliderStr);
};