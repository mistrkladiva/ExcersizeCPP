#pragma once
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const float GAME_AREA_OFFSET = 100.f;
const sf::FloatRect GAME_AREA = {
    100.f,
    100.f,
    (float)WINDOW_WIDTH - GAME_AREA_OFFSET * 2,
    (float)WINDOW_HEIGHT - GAME_AREA_OFFSET * 2
};
