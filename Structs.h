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
	sf::FloatRect textureSize;
    sf::FloatRect spriteCollider;
};

enum class Direction {
    Idle = 0,
	Down = 1,
	Right = 2,
	Up = 3,
	Left = 4,
	dialogue = 5
};

struct TileCollider {
    bool active = false;
	std::string name = "";
    sf::FloatRect rect;
    int type;            // 0 = nic, 1 = wall, 2 = trap, 3 = building...
    // nebo tøeba enum
};



enum class eventConditions {
	isCollideWithNpc = 0,
	isEventComplete = 1
};

enum class eventActions {
	startDialogue = 0,
	eventComplete = 1
};

struct conditionData
{
	eventConditions conditionType;
	std::string conditionValue;
};

struct actionData
{
	eventActions actionType;
	std::string actionValue;
};

struct eventData
{
	std::string eventName;
	std::vector<conditionData> eventConditions;
	std::vector<actionData> eventActions;
	bool eventCompleted = false;
};



// Definice struktur pro mapu a jejich serializaci pomocí nlohmann::json

// Užiteèný alias pro mapu atributù, kde klíè i hodnota jsou stringy
using Attributes = std::map<std::string, std::string>;

// --- 1. Struktura pro jednotlivou dlaždici (Tile) ---
struct Tile {
    std::string id;
    int x;
    int y;
    // Pole 'attributes' je volitelné, pokud se v JSON nevyskytuje, bude mapa prázdná
	std::optional<Attributes> attributes;
};

inline void from_json(const nlohmann::json& j, Tile& t)
{
    j.at("id").get_to(t.id);
    j.at("x").get_to(t.x);
    j.at("y").get_to(t.y);

    if (j.contains("attributes")) {
        t.attributes = j.at("attributes").get<Attributes>();
    }
    else {
        t.attributes = std::nullopt;
    }
}

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
    float mapWidth;
    float mapHeight;
    std::vector<Layer> layers; // Seznam objektù Layer
};

// Makro pro automatickou serializaci/deserializaci struktury MapData
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MapData, tileSize, mapWidth, mapHeight, layers)