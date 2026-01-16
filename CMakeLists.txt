cmake_minimum_required(VERSION 3.20)
project(LekceSprite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------
# Zdrojové soubory
# -------------------------------------------------
add_executable(LekceSprite
    LekceSprite.cpp
    Player.cpp
    Npc.cpp
    AudioManager.cpp
    DialogueManager.cpp
    GameEventsManager.cpp
    MapGenerator.cpp
    MapJsonParse.cpp
    Globals.cpp
)

set_target_properties(LekceSprite PROPERTIES
    OUTPUT_NAME "tajemstvi_prstenu"
)

# -------------------------------------------------
# SFML
# -------------------------------------------------
find_package(SFML 2.5 REQUIRED COMPONENTS
    system window graphics audio
)

target_include_directories(LekceSprite PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(LekceSprite
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)