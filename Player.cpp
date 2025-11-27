#include "Player.h"

Player::Player(sf::RenderWindow* window, sf::Texture& spritesheet, SpriteCharacter sprt)
	: m_window(window)
	, m_spritesheet(spritesheet)
	, m_sprt(sprt)
{
	loadCharacterSprites();
	// clock už je implicitnì spuštìný pøi vytvoøení
	m_timeAccumulator = sf::Time::Zero;
	m_currentFrameIndex = 0;
	m_lastDirection = -2;
}

void Player::update(int direction, sf::Vector2f deltaPos)
{
	
	if (direction == -1) {
		m_clock.restart();
		return;
	}
		

	if (direction != m_lastDirection) {
		m_currentFrameIndex = 0;
		m_timeAccumulator = sf::Time::Zero;
		m_lastDirection = direction;
	}

	animation(direction);
	move(deltaPos);
}

void Player::draw()
{
	m_window->draw(m_currentFrame);
}

/// <summary>
/// Posune hráèe o zadaný vektor s uplatnìním rychlosti, omezí pohyb na povolenou herní oblast a aktualizuje pozici grafického rámce.
/// </summary>
/// <param name="deltaPos">Vektor posunu (x, y). Hodnoty jsou vynásobeny rychlostí hráèe a pøièteny k aktuální pozici;
/// pøesun se provede pouze pokud výsledná pozice a oblast 100×100 od ní jsou uvnitø GAME_AREA.</param>
void Player::move(sf::Vector2f deltaPos)
{
	sf::Vector2f newPos = { 
		m_playerPos.x + m_playerSpeed * deltaPos.x,
		m_playerPos.y + m_playerSpeed * deltaPos.y 
	};

	if (isCollision(newPos)) {
		std::cout << "Kolize!\n";
		m_currentFrame.setPosition(m_playerPos);
		return;
		
	}

	if (GAME_AREA.contains(newPos.x, newPos.y) &&
		GAME_AREA.contains(newPos.x + 100, newPos.y + 100))
	{
		m_playerPos = newPos;
	}

	m_currentFrame.setPosition(m_playerPos);
}

bool Player::isCollision(sf::Vector2f& playerPos)
{
	// Lokalní rozmìry sprite (width/height) - safe
	sf::FloatRect local = m_currentFrame.getLocalBounds();
	sf::Vector2f origin = m_currentFrame.getOrigin();

	// Vypoèti AABB pro novou pozici (newPos je svìtová pozice, kterou chceš použít)
	sf::FloatRect playerBound{
		playerPos.x - origin.x,
		playerPos.y - origin.y,
		local.width,
		local.height
	};


	//int leftTile = std::max(0, (int)std::floor(playerBound.left / tileSize));
	//int rightTile = std::min(mapWidthInTiles - 1, (int)std::floor((playerBound.left + playerBound.width - 1) / tileSize));
	//int topTile = std::max(0, (int)std::floor(playerBound.top / tileSize));
	//int bottomTile = std::min(mapHeightInTiles - 1, (int)std::floor((playerBound.top + playerBound.height - 1) / tileSize));

	//for (int ty = topTile; ty <= bottomTile; ++ty) {
	//	for (int tx = leftTile; tx <= rightTile; ++tx) {
	//		// získej index dlaždice (napø. ty * mapWidthInTiles + tx)
	//		// nebo použij 2D pole booleanù `isColliderTile[ty][tx]`
	//		if (isColliderTile[ty][tx]) {
	//			sf::FloatRect tileRect(tx * tileSize, ty * tileSize, tileSize, tileSize);
	//			if (playerBound.intersects(tileRect)) return true;
	//		}
	//	}
	//}

	// TODO: Použít spatial partitioning pro optimalizaci, pokud je potøeba
	for (auto& collider : playerColliders) {
		if (playerBound.intersects(collider)) {
			return true;
		}
	}
	return false;
}

/// <summary>
/// Naète jednotlivé snímky (sf::Sprite) postavy ze spritesheetu a uloží je do èlenské promìnné m_frames.
/// každá øada v m_frames odpovídá jednomu smìru animace (idle, left, right, up, down).
/// </summary>
void Player::loadCharacterSprites()
{
	m_frames.resize(m_sprt.frameRow);

	for (int row = 0; row < m_sprt.frameRow; row++)
	{
		for (int col = 0; col < m_sprt.frameCol; col++)
		{
			int x = col * (int)m_sprt.textureSize.width ;
			int y = row * (int)m_sprt.textureSize.height ;

			sf::Sprite spr;
			spr.setTexture(m_spritesheet);
			spr.setTextureRect(sf::IntRect(x, y, (int)m_sprt.textureSize.width, (int)m_sprt.textureSize.height));
			spr.setOrigin(m_sprt.textureSize.width / 2, m_sprt.textureSize.height / 2);
			m_frames[row].push_back(spr);
		}
	}
}

/// <summary>
/// Aktualizuje aktuální snímek animace hráèe podle smìru a akumulovaného èasu.
/// </summary>
/// <param name="direction">Index smìru animace; používá se k výbìru seznamu snímkù pro daný smìr.</param>
void Player::animation(int direction)
{
	m_timeAccumulator += m_clock.restart();

	if (m_timeAccumulator.asSeconds() >= m_frameDuration) {
		m_timeAccumulator -= sf::seconds(m_frameDuration);
		m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames[direction].size();
	}

	m_currentFrame = m_frames[direction][m_currentFrameIndex];
}