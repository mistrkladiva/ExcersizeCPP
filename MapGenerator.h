#pragma once
#include <iostream>
#include "Structs.h"
#include "Globals.h"

class MapGenerator
{
public:
    MapGenerator(sf::RenderWindow* window, sf::Texture& mapSpritesheet, MapData& mapData, std::vector<sf::Sprite*>& charactersSprite);
    void drawMap();

private:
    sf::RenderWindow* m_window;
    sf::Texture& m_mapSpritesheet;
    MapData& m_mapData;

    std::vector<sf::Sprite> m_tiles;
    std::vector<sf::Sprite> m_mapSprites;
    std::vector<sf::Sprite> m_topLayer;

    // HLAVNÍ ZMĚNA: ukazatele, ne kopie
    std::vector<sf::Sprite*> m_overlappingLayer;

    std::vector<sf::Sprite*> m_charactersSprite;


    void loadTiles();
    sf::FloatRect parseColliderString(const std::string& colliderStr);
};