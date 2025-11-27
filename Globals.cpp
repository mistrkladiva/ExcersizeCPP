#include "Globals.h"

const float WINDOW_WIDTH = 1024;
const float WINDOW_HEIGHT = 768;
const float GAME_AREA_OFFSET = 100.f;
const sf::FloatRect GAME_AREA{
    100.f,
    100.f,
    WINDOW_WIDTH - GAME_AREA_OFFSET * 2,
    WINDOW_HEIGHT - GAME_AREA_OFFSET * 2
};

std::vector<sf::FloatRect> playerColliders;