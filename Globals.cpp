#include "Globals.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const float GAME_AREA_OFFSET = 100.f;
const sf::FloatRect GAME_AREA{
    100.f,
    100.f,
    WINDOW_WIDTH - GAME_AREA_OFFSET * 2,
    WINDOW_HEIGHT - GAME_AREA_OFFSET * 2
};




//void pokus() {
//    // Pøedpokládejme, že JSON, který jste poskytl, je uložen v souboru 'mapa.json'
//    MapData loaded_map = LoadMapFromJsonFile("assets/map.json");
//
//    if (loaded_map.layers.empty()) {
//        std::cout << "Naèítání selhalo nebo mapa je prázdná." << std::endl;
//        return;
//    }
//
//    // Ukázka pøístupu k datùm:
//    std::cout << "\n--- Naètená data ---" << std::endl;
//    std::cout << "Velikost dlaždice (tileSize): " << loaded_map.tileSize << std::endl;
//    std::cout << "Šíøka mapy (mapWidth): " << loaded_map.mapWidth << std::endl;
//    std::cout << "Poèet vrstev (layers): " << loaded_map.layers.size() << std::endl;
//
//    // První vrstva
//    const auto& first_layer = loaded_map.layers[0];
//    std::cout << "\nDetail první vrstvy:" << std::endl;
//    std::cout << "  Jméno: " << first_layer.name << std::endl;
//    std::cout << "  Má kolizi (collider): " << (first_layer.collider ? "Ano" : "Ne") << std::endl;
//    std::cout << "  Poèet dlaždic: " << first_layer.tiles.size() << std::endl;
//
//    // Detaily první dlaždice v první vrstvì
//    if (!first_layer.tiles.empty()) {
//        const auto& first_tile = first_layer.tiles[0];
//        std::cout << "  První dlaždice: ID=" << first_tile.id << ", X=" << first_tile.x << ", Y=" << first_tile.y << std::endl;
//    }
//
//    // Ukázka pøístupu k volitelným 'attributes' (napø. ve vrstvì "bacground")
//    /*for (const auto& layer : loaded_map.layers) {
//        if (layer.name == "bacground" && !layer.tiles.empty()) {
//            std::cout << "\nAtributy u dlaždic ve vrstvì 'bacground':" << std::endl;
//            const auto& tile_with_attr = layer.tiles[0];
//            if (!tile_with_attr.attributes.empty()) {
//                std::cout << "  První dlaždice s ID " << tile_with_attr.id << " má atribut 'grass': "
//                    << tile_with_attr.attributes.at("grass") << std::endl;
//            }
//            break;
//        }
//    }*/
//}