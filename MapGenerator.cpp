#include "MapGenerator.h"

MapGenerator::MapGenerator(sf::RenderWindow* window, sf::Texture& mapSpritesheet, MapData& mapData)
	: m_window(window),
	m_mapSpritesheet(mapSpritesheet),
	m_mapData(mapData)
{
	loadTiles();
}

void MapGenerator::loadTiles()
{
	int tilesPerRow = m_mapSpritesheet.getSize().x / m_mapData.tileSize;
	int tilesPerCol = m_mapSpritesheet.getSize().y / m_mapData.tileSize;

	for (int row = 0; row < tilesPerRow; row++)
	{
		for (int col = 0; col < tilesPerRow; col++)
		{
			int x = col * m_mapData.tileSize;
			int y = row * m_mapData.tileSize;

			sf::Sprite spr;
			spr.setTexture(m_mapSpritesheet);
			spr.setTextureRect(sf::IntRect(x, y, m_mapData.tileSize, m_mapData.tileSize));

			m_tiles.push_back(spr);
		}
	}

	for (int i = (int)m_mapData.layers.size() - 1; i >= 0; --i)
	{
		for (auto& tile : m_mapData.layers[i].tiles)
		{
			

			if (tile.attributes.has_value()) {
				auto& attrs = tile.attributes.value();
				std::cout << "Tile ID: " << tile.id << " Obsahuje attributy ";
			}

			int index = std::stoi(tile.id);
			if (index < 0 || index >= m_tiles.size()) {
				std::cerr << "Chybný tile index: " << index << std::endl;
				continue;
			}
			sf::Sprite tileSprite(m_tiles[index]);
			
			tileSprite.setPosition((float)tile.x * m_mapData.tileSize, (float)tile.y * m_mapData.tileSize);

			if (m_mapData.layers[i].collider)
			{
				playerColliders.push_back(
					sf::FloatRect(tileSprite.getPosition().x,
					tileSprite.getPosition().y,
					m_mapData.tileSize,
					m_mapData.tileSize)
				);
			}
			m_mapSprites.push_back(tileSprite);
		}
	}
}

void MapGenerator::drawMap()
{
	for (auto& tile : m_mapSprites)
	{
		m_window->draw(tile);
	}
}
