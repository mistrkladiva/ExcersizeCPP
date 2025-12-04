#pragma once
#include <SFML/Graphics.hpp>
#include "Structs.h"
#include "MapJsonParse.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

extern const float WINDOW_WIDTH;
extern const float WINDOW_HEIGHT;
extern const float GAME_AREA_OFFSET;
extern const sf::FloatRect GAME_AREA;
extern std::vector<std::vector<TileCollider>> tileGrid;
extern MapData MAP_DATA;

extern Tile& get_interactive_item_tile(std::string interactiveName);
extern bool insert_new_item_tile(const Tile& newTile);