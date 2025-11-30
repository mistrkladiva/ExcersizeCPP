#include "MapGenerator.h"
#include <sstream>

MapGenerator::MapGenerator(sf::RenderWindow* window, sf::Texture& mapSpritesheet, MapData& mapData, sf::Sprite& playerSprite)
    : m_window(window),
    m_mapSpritesheet(mapSpritesheet),
    m_mapData(mapData),
    m_playerSprite(playerSprite)
{
    loadTiles();
}

void MapGenerator::loadTiles()
{
    int tilesPerRow = m_mapSpritesheet.getSize().y / m_mapData.tileSize;
    int tilesPerCol = m_mapSpritesheet.getSize().x / m_mapData.tileSize;

    // načti tilesheet do vektoru
    for (int row = 0; row < tilesPerRow; row++)
    {
        for (int col = 0; col < tilesPerCol; col++)
        {
            int x = col * m_mapData.tileSize;
            int y = row * m_mapData.tileSize;

            sf::Sprite spr;
            spr.setTexture(m_mapSpritesheet);
            spr.setTextureRect(sf::IntRect(x, y, m_mapData.tileSize, m_mapData.tileSize));

            m_tiles.push_back(spr);
        }
    }

    tileGrid.resize((int)m_mapData.mapHeight, std::vector<TileCollider>((int)m_mapData.mapWidth));
    m_overlappingLayer.clear();

    // projdi vrstvy
    for (int i = (int)m_mapData.layers.size() - 1; i >= 0; --i)
    {
        for (auto& tile : m_mapData.layers[i].tiles)
        {
            int index = std::stoi(tile.id);
            if (index < 0 || index >= (int)m_tiles.size()) {
                std::cerr << "Chybný tile index: " << index << std::endl;
                continue;
            }

            sf::Sprite tileSprite(m_tiles[index]);
            tileSprite.setPosition((float)tile.x * m_mapData.tileSize, (float)tile.y * m_mapData.tileSize);

			// dlaždice, které jsou stále nad hráčem (střechy, stromy)
            if (m_mapData.layers[i].name == "top_layer") {
                m_topLayer.push_back(tileSprite);
                continue;
            }

			// dlaždice s vlastním colliderem se řídí z-indexem podle Y pozice hráče
            if (tile.attributes.has_value()) {
                auto& attrs = tile.attributes.value();

                if (attrs.contains("custom_collider")) {

                    sf::FloatRect customColliderRect = parseColliderString(attrs["custom_collider"]);

                    tileGrid[tile.y][tile.x].active = true;
                    tileGrid[tile.y][tile.x].rect = sf::FloatRect(
                        tileSprite.getPosition().x + customColliderRect.left,
                        tileSprite.getPosition().y + customColliderRect.top,
                        customColliderRect.width,
                        customColliderRect.height
                    );

                    // tento tile patří do overlapping vrstvy
                    m_mapSprites.push_back(tileSprite);
                    m_overlappingLayer.push_back(&m_mapSprites.back());

                    continue;
                }
            }

			// dlaždice beze změny collideru (defaultně je collider je o velikosti dlaždice)
            if (m_mapData.layers[i].collider)
            {
                tileGrid[tile.y][tile.x].active = true;
                tileGrid[tile.y][tile.x].rect = sf::FloatRect(
                    tileSprite.getPosition().x,
                    tileSprite.getPosition().y,
                    (float)m_mapData.tileSize,
                    (float)m_mapData.tileSize
                );
            }
			// statické dlaždice jdou do spodní vrstvy
            m_mapSprites.push_back(tileSprite);
        }
    }
	// přidej hráče do overlapping vrstvy jako POINTER pro výpočet z-indexu
    m_overlappingLayer.push_back(&m_playerSprite);
}

/// <summary>
/// Vykreslí mapu do okna ve třech krocích: spodní statická vrstva,
/// seřazení a vykreslení překrývajících se objektů podle Y (Y‑sort)
/// a následná horní vrstva vždy nahoře.
/// </summary>
void MapGenerator::drawMap()
{
    // 1) spodní vrstva (statická)
    for (auto& tile : m_mapSprites) {
        m_window->draw(tile);
    }
    // 2) Y-SORT pro hráče a overlappující věci
    std::vector<sf::Sprite*> sorted = m_overlappingLayer;

    std::sort(sorted.begin(), sorted.end(), [](sf::Sprite* a, sf::Sprite* b) {
        float ay = a->getGlobalBounds().top + a->getGlobalBounds().height;
        float by = b->getGlobalBounds().top + b->getGlobalBounds().height;
        return ay < by;
        });

    for (auto spr : sorted) {
        m_window->draw(*spr);
    }
    // 3) top layer (střechy, stromy)
    for (auto& tile : m_topLayer) {
        m_window->draw(tile);
    }
}

/// <summary>
/// parsuje string ve formátu "left,top,width,height" ("0,0,128,128") na sf::FloatRect
/// získaný z atributu custom_collider v JSONu
/// </summary>
/// <param name="colliderStr"></param>
/// <returns></returns>
sf::FloatRect MapGenerator::parseColliderString(const std::string& colliderStr)
{
    std::string segment;
    std::vector<std::string> seglist;
    sf::FloatRect tileCollisionRect;

    std::stringstream ss(colliderStr);
    while (std::getline(ss, segment, ',')) {
        seglist.push_back(segment);
    }

    if (seglist.size() != 4) {
        std::cerr << "Nesprávný počet segmentů v collider stringu: " << colliderStr << "\n";
        return tileCollisionRect;
    }

    try {
        float left = std::stof(seglist[0]);
        float top = std::stof(seglist[1]);
        float width = std::stof(seglist[2]);
        float height = std::stof(seglist[3]);
        tileCollisionRect = { left, top, width, height };
    }
    catch (...) {
        std::cerr << "Nepodařilo se parsovat collider string\n";
    }

    return tileCollisionRect;
}
