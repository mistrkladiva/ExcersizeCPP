#include "Player.h"

Player::Player(sf::RenderWindow* window, GameEventsManager& gameEventsManager, sf::Texture& spritesheet, SpriteCharacter sprt)
	: m_window(window)
	, m_spritesheet(spritesheet)
	, m_sprt(sprt)
	, m_gameEventsManager(gameEventsManager)
{
	loadCharacterSprites();
	m_playerPos = getNpcPosInTileGrid(sf::Vector2(7, 11));
	// clock už je implicitně spuštěný při vytvoření
	m_timeAccumulator = sf::Time::Zero;
	m_currentFrameIndex = 0;
	m_lastDirection = -2;
}

void Player::update(int direction, sf::Vector2f deltaPos)
{
	// může se použít k nějakému stavu, např. pauza nebo dialog
	if (direction == -1) {
		m_clock.restart();
		return;
	}

	// korekce diagonálních směrů pro animaci
	if ((deltaPos.x == -1 && deltaPos.y == -1) || (deltaPos.x == -1 && deltaPos.y == 1)) {
		direction = 4;
	}
	if ((deltaPos.x == 1 && deltaPos.y == 1) || (deltaPos.x == 1 && deltaPos.y == -1)) {
		direction = 2;
	}

	if (direction != m_lastDirection) {
		m_currentFrameIndex = 0;
		m_timeAccumulator = sf::Time::Zero;
		m_lastDirection = direction;
	}

	animation(direction);
	move(deltaPos);
	//m_gameEventsManager.setDialoguePosition({ m_playerPos.x, m_playerPos.y - 100.f });
}

// vykreslování hráče řeší MapGenerator přes referenci na m_currentFrame
void Player::draw()
{
	/*if (m_isDialogueActive)
		m_gameEventsManager.draw();*/
}


/// <summary>
/// Posune hráče o zadaný vektor s uplatněním rychlosti, omezí pohyb na povolenou herní oblast a aktualizuje pozici grafického rámce.
/// </summary>
/// <param name="deltaPos">Vektor posunu (x, y). Hodnoty jsou vynásobeny rychlostí hráče a přičteny k aktuální pozici;
/// přesun se provede pouze pokud výsledná pozice a oblast 100×100 od ní jsou uvnitř GAME_AREA.</param>
void Player::move(sf::Vector2f deltaPos)
{
	// TODO: ošetřit pohyb diagonálně (normalizovat vektor) při diagonálním pohybu sprite vlevo nebo vpravo
	sf::Vector2f newPos = {
		m_playerPos.x + m_playerSpeed * deltaPos.x,
		m_playerPos.y + m_playerSpeed * deltaPos.y
	};

	if (isCollision(newPos)) {
		m_currentFrame.setPosition(m_playerPos);
		int row = m_collidedTilePos.y;
		int col = m_collidedTilePos.x;

		// současná kolizní dlaždice (x,y)
		sf::Vector2i currentTile(col, row);

		// TODO: při kontaktu s npc nastavit sprite npc na talk
		if (tileGrid[row][col].name != "") {
			if (m_lastColliderTile != currentTile) {
				// nový vstup do kolizního boxu této dlaždice
				m_lastColliderTile = currentTile;
				m_gameEventsManager.checkEvent(tileGrid[row][col].name);
			}
		}
		return;
	} else
	{
		// žádná kolize -> umožnit znovuvstup později
		if (m_lastColliderTile.x != -1 || m_lastColliderTile.y != -1) {
			m_lastColliderTile = sf::Vector2i(-1, -1);
		}
	}

	m_isDialogueActive = false;
	m_playerPos = newPos;
	m_currentFrame.setPosition(m_playerPos);
}

bool Player::isCollision(sf::Vector2f& playerPos)
{
	// Lokalní rozměry sprite (width/height) - safe
	sf::FloatRect local = m_currentFrame.getLocalBounds();
	sf::Vector2f origin = m_currentFrame.getOrigin();

	// Vypočti AABB pro novou pozici (newPos je světová pozice, kterou chceš použít)
	/*sf::FloatRect playerBound{
		playerPos.x - origin.x,
		playerPos.y - origin.y,
		local.width,
		local.height
	};*/

	// m_sprt.spriteCollider.left a top je vždy nula posun kolizního obdélníku je na základě pozice spritu
	sf::FloatRect playerBoxCollider{
		playerPos.x - 20,
		playerPos.y + 30,
		m_sprt.spriteCollider.width,
		m_sprt.spriteCollider.height
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


/// <summary>
/// Načte jednotlivé snímky (sf::Sprite) postavy ze spritesheetu a uloží je do členské proměnné m_frames.
/// každá řada v m_frames odpovídá jednomu směru animace (idle, left, right, up, down).
/// </summary>
void Player::loadCharacterSprites()
{
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
			m_frames[row].push_back(spr);
		}
	}
}

/// <summary>
/// Aktualizuje aktuální snímek animace hráče podle směru a akumulovaného času.
/// </summary>
/// <param name="direction">Index směru animace; používá se k výběru seznamu snímků pro daný směr.</param>
void Player::animation(int direction)
{
	m_timeAccumulator += m_clock.restart();

	if (m_timeAccumulator.asSeconds() >= m_frameDuration) {
		m_timeAccumulator -= sf::seconds(m_frameDuration);
		m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames[direction].size();
	}

	m_currentFrame = m_frames[direction][m_currentFrameIndex];
}

sf::Sprite& Player::getCurrentFrame()
{
	return m_currentFrame;
}

sf::Vector2f Player::getNpcPosInTileGrid(sf::Vector2i gridPos)
{
	// výpočet umístění npc na střed dlaždice mřížky
	float centerX = std::floorf(((float)gridPos.x * MAP_DATA.tileSize) + (MAP_DATA.tileSize / 2));
	float centerY = std::floorf(((float)gridPos.y * MAP_DATA.tileSize) + (MAP_DATA.tileSize / 2));

	return sf::Vector2f(centerX, centerY);;
}
