#pragma once
#include <SFML/Graphics.hpp>
#include <json.hpp>

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
	sf::IntRect textureSize;
};

enum class Direction {
	Down = 0,
	Right = 1,
	Up = 2,
	Left = 3,
	Idle = -1
};


// Užiteèný alias pro mapu atributù, kde klíè i hodnota jsou stringy
//using Attributes = std::map<std::string, std::string>;

// --- 1. Struktura pro jednotlivou dlaždici (Tile) ---
struct Tile {
    std::string id;
    int x;
    int y;
    // Pole 'attributes' je volitelné, pokud se v JSON nevyskytuje, bude mapa prázdná
    //Attributes attributes;
};


// Makro pro automatickou serializaci/deserializaci struktury Tile
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Tile, id, x, y)

// --- 2. Struktura pro vrstvu mapy (Layer) ---
struct Layer {
    std::string name;
    std::vector<Tile> tiles; // Seznam objektù Tile
    bool collider;
};

// Makro pro automatickou serializaci/deserializaci struktury Layer
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Layer, name, tiles, collider)

// --- 3. Hlavní struktura mapy (MapData) ---
struct MapData {
    int tileSize;
    int mapWidth;
    int mapHeight;
    std::vector<Layer> layers; // Seznam objektù Layer
};

// Makro pro automatickou serializaci/deserializaci struktury MapData
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MapData, tileSize, mapWidth, mapHeight, layers)