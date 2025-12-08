#include "MapJsonParse.h"

///**
// * Načte JSON soubor z cesty a deserializuje ho do struktury MapData.
// * @param filepath Cesta k JSON souboru.
// * @return Objekt MapData, nebo prázdný objekt v případě chyby.
// */
MapData MapJsonParse::LoadMapFromJsonFile(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!std::filesystem::exists(filepath)) {
        std::cerr << "Soubor neexistuje: " << filepath << std::endl;
        return MapData{};
    }

    if (!file.is_open()) {
        std::cerr << "CHYBA: Nelze otevřít soubor: " << filepath << std::endl;
        return MapData{}; // Vrací prázdnou strukturu
    }

    try {
        // 1. Parsuje JSON ze souboru
        nlohmann::json j = nlohmann::json::parse(file, nullptr, true, true);

        // 2. Deserializace JSON objektu do C++ struktury
        MapData map_data = j.get<MapData>();

        std::cout << "JSON načten a úspěšně deserializován do MapData." << std::endl;
        return map_data;

    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "CHYBA: Chyba při parsování JSON: " << e.what() << " (Pozice: " << e.byte << ")" << std::endl;
        return MapData{};
    }
    catch (const nlohmann::json::type_error& e) {
        // Chyba, pokud se datové typy v JSON neshodují se strukturou (např. string místo int)
        std::cerr << "CHYBA: Chyba typu při deserializaci: " << e.what() << std::endl;
        return MapData{};
    }
    catch (const std::exception& e) {
        std::cerr << "Nastala neočekávaná chyba: " << e.what() << std::endl;
        return MapData{};
    }
}