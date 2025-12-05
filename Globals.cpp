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

extern MapData MAP_DATA = MapJsonParse::LoadMapFromJsonFile("assets/map-level-01.json");
//extern std::vector<std::vector<TileCollider>> tileGrid = {};
//extern std::vector<std::vector<TileCollider>> tileGrid.resize((int)MAP_DATA.mapHeight, std::vector<TileCollider>((int)MAP_DATA.mapWidth));
extern std::vector<std::vector<TileCollider>> tileGrid((int)MAP_DATA.mapHeight, std::vector<TileCollider>((int)MAP_DATA.mapWidth));



/// <summary>
/// Vyhledá ve vrstvì s názvem "items" dlaždici, která má atribut "interactive" se zadaným názvem.
/// </summary>
/// <param name="interactiveName">Název hodnoty atributu "interactive", kterou hledáme na dlaždici.</param>
/// <returns>Reference na nalezenou Tile. Pokud vrstva "items" neexistuje, je vyhozena std::runtime_error.
/// Pokud žádná odpovídající dlaždice není nalezena, funkce vypíše zprávu do std::cout a vrátí referenci na novì alokovaný objekt Tile s id "-1"
/// (pozn.: tento objekt je alokován pomocí new, takže vlastnictví/životnost mùže vést k úniku pamìti, pokud není správnì uvolnìn).</returns>
Tile& get_interactive_item_tile(std::string interactiveName)
{
    // Najdi vrstvu s názvem "items"
    auto itemLayerIt = std::find_if(
        MAP_DATA.layers.begin(),
        MAP_DATA.layers.end(),
        [](const Layer& layer) { return layer.name == "items"; }
    );

    if (itemLayerIt == MAP_DATA.layers.end()) {
        throw std::runtime_error("Vrstva 'items' nebyla nalezena v MAP_DATA.");
    }

    Layer& itemLayer = *itemLayerIt;

    // Najdi dlaždici s atributem "interactive"
    auto tileLayerIt = std::find_if(
        itemLayer.tiles.begin(),
        itemLayer.tiles.end(),
        [&interactiveName](const Tile& tile) {
            return tile.attributes.has_value()
                && tile.attributes->find("interactive") != tile.attributes->end()
                && tile.attributes->at("interactive") == interactiveName;
        }
    );

    if (tileLayerIt == itemLayer.tiles.end()) {
		
		std::cout << "Interaktivní dlaždice nebyla nalezena ve vrstvì 'items'." << std::endl;

		Tile& emptyTile = *(new Tile{});
		emptyTile.id = "-1";
        return emptyTile;
    }

    return *tileLayerIt;
}

bool insert_new_item_tile(const Tile& newTile)
{
    // Najdi vrstvu s názvem "items"
    auto itemLayerIt = std::find_if(
        MAP_DATA.layers.begin(),
        MAP_DATA.layers.end(),
        [](const Layer& layer) { return layer.name == "items"; }
    );

    if (itemLayerIt == MAP_DATA.layers.end()) {
        std::cout << "Vrstva 'items' nebyla nalezena v MAP_DATA." << std::endl;
        return false;
    }

    Layer& itemLayer = *itemLayerIt;

    itemLayer.tiles.push_back(newTile);
    return true;
}
