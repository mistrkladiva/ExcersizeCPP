#include "Npc.h"

Npc::Npc(sf::RenderWindow* window, sf::Texture& spritesheet, SpriteCharacter& sprt, sf::Vector2i gridPos)
	: m_window(window)
	, m_spritesheet(spritesheet)
	, m_sprt(sprt)
	, m_dialogue(window)
	, m_gridPos(gridPos)
{
	m_npcPos = getNpcPosInTileGrid(m_gridPos);
	loadCharacterSprites();
	// clock už je implicitnì spuštìný pøi vytvoøení
	m_timeAccumulator = sf::Time::Zero;
	m_currentFrameIndex = 0;
	m_lastDirection = -2;
}

void Npc::update()
{
	animation(0);
}

// vykreslování hráèe øeší MapGenerator pøes referenci na m_currentFrame
void Npc::draw()
{
	//m_window->draw(m_currentFrame);
	m_window->draw(m_npcColliderShape);
}

/// <summary>
/// Posune hráèe o zadaný vektor s uplatnìním rychlosti, omezí pohyb na povolenou herní oblast a aktualizuje pozici grafického rámce.
/// </summary>
/// <param name="deltaPos">Vektor posunu (x, y). Hodnoty jsou vynásobeny rychlostí hráèe a pøièteny k aktuální pozici;
/// pøesun se provede pouze pokud výsledná pozice a oblast 100×100 od ní jsou uvnitø GAME_AREA.</param>
void Npc::move(sf::Vector2f deltaPos)
{
	sf::Vector2f newPos = {
		m_npcPos.x + m_playerSpeed * deltaPos.x,
		m_npcPos.y + m_playerSpeed * deltaPos.y
	};

	if (isCollision(newPos)) {
		m_currentFrame.setPosition(m_npcPos);
		int row = m_collidedTilePos.y;
		int col = m_collidedTilePos.x;

		if (tileGrid[row][col].name != "") {
			if (tileGrid[row][col].name == "barrel") {
				m_dialogue.setDialogueMessage("It's a barrel. It looks empty.");
				m_isDialogueActive = true;
			}
		}
		return;
	}

	m_npcPos = newPos;
	m_currentFrame.setPosition(m_npcPos);
}

bool Npc::isCollision(sf::Vector2f& playerPos)
{
	// Lokalní rozmìry sprite (width/height) - safe
	sf::FloatRect local = m_currentFrame.getLocalBounds();
	sf::Vector2f origin = m_currentFrame.getOrigin();

	// Vypoèti AABB pro novou pozici (newPos je svìtová pozice, kterou chceš použít)
	/*sf::FloatRect playerBound{
		playerPos.x - origin.x,
		playerPos.y - origin.y,
		local.width,
		local.height
	};*/

	sf::FloatRect playerBoxCollider{
		playerPos.x - 20,
		playerPos.y + 30,
		50,
		20
	};

	const int tileSize = MAP_DATA.tileSize;

	int leftTile = std::max(0, (int)std::floor(playerBoxCollider.left / tileSize));
	int rightTile = std::min((int)MAP_DATA.mapWidth - 1, (int)std::floor((playerBoxCollider.left + playerBoxCollider.width) / tileSize));
	int topTile = std::max(0, (int)std::floor(playerBoxCollider.top / tileSize));
	int bottomTile = std::min((int)MAP_DATA.mapHeight - 1, (int)std::floor((playerBoxCollider.top + playerBoxCollider.height) / tileSize));

	for (int y = topTile; y <= bottomTile; ++y)
	{
		for (int x = leftTile; x <= rightTile; ++x)
		{
			if (!tileGrid[y][x].active)
				continue;

			if (playerBoxCollider.intersects(tileGrid[y][x].rect)) {
				m_collidedTilePos = sf::Vector2i(x, y);
				return true;
			}
		}
	}

	return false;
}

sf::Vector2f Npc::getNpcPosInTileGrid(sf::Vector2i& gridPos)
{
	// výpoèet umístìní npc na støed dlaždice møížky
	float centerX = std::floorf(((float)gridPos.x * MAP_DATA.tileSize) + (MAP_DATA.tileSize / 2));
	float centerY = std::floorf(((float)gridPos.y * MAP_DATA.tileSize) + (MAP_DATA.tileSize / 2));

	return sf::Vector2f(centerX, centerY);;
}


/// <summary>
/// Naète jednotlivé snímky (sf::Sprite) postavy ze spritesheetu a uloží je do èlenské promìnné m_frames.
/// každá øada v m_frames odpovídá jednomu smìru animace (idle, left, right, up, down).
/// </summary>
void Npc::loadCharacterSprites()
{
	// nastavení kolizního obdélníku je od 0,0 zde ještì není nastaven origin
	// v pøipadì pohybu npc bude tøeba aktualizovat pozici kolizního boxu a ukládání do tileGrid
	sf::FloatRect playerBoxCollider{
		m_npcPos.x + m_sprt.spriteCollider.left,
		m_npcPos.y + m_sprt.spriteCollider.top,
		m_sprt.spriteCollider.width,
		m_sprt.spriteCollider.height
	};

	m_npcColliderShape.setSize(sf::Vector2f(playerBoxCollider.width, playerBoxCollider.height));
	m_npcColliderShape.setPosition((playerBoxCollider.left), (playerBoxCollider.top));
	m_npcColliderShape.setFillColor(sf::Color(255, 0, 0, 100)); // èervená s prùhledností

	m_tileCollider = { true, m_sprt.name, playerBoxCollider, 1 };

	tileGrid[m_gridPos.y][m_gridPos.x] = m_tileCollider;

	m_frames.resize(m_sprt.frameRow);

	for (int row = 0; row < m_sprt.frameRow; row++)
	{
		for (int col = 0; col < m_sprt.frameCol; col++)
		{
			int x = col * (int)m_sprt.textureSize.width + (int)m_sprt.textureSize.left;
			int y = row * (int)m_sprt.textureSize.height + (int)m_sprt.textureSize.top;

			sf::Sprite spr;
			spr.setTexture(m_spritesheet);
			spr.setTextureRect(sf::IntRect(x, y, (int)m_sprt.textureSize.width, (int)m_sprt.textureSize.height));
			spr.setOrigin(m_sprt.textureSize.width / 2, m_sprt.textureSize.height / 2);
			// tvrdé nastavení pozice spritù, pokud se bude pohybovat, je tøeba aktualizovat m_currentFrame pøi pohybu
			spr.setPosition(m_npcPos);
			m_frames[row].push_back(spr);
			
		}
	}
}

/// <summary>
/// Aktualizuje aktuální snímek animace hráèe podle smìru a akumulovaného èasu.
/// </summary>
/// <param name="direction">Index smìru animace; používá se k výbìru seznamu snímkù pro daný smìr.</param>
void Npc::animation(int direction)
{
	m_timeAccumulator += m_clock.restart();

	if (m_timeAccumulator.asSeconds() >= m_frameDuration) {
		m_timeAccumulator -= sf::seconds(m_frameDuration);
		m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames[direction].size();
	}

	m_currentFrame = m_frames[direction][m_currentFrameIndex];
}

sf::Sprite& Npc::getCurrentFrame()
{
	return m_currentFrame;
}