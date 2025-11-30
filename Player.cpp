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

// vykreslování hráèe øeší MapGenerator pøes referenci na m_currentFrame
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
		m_currentFrame.setPosition(m_playerPos);
		return;
	}

	/*if (GAME_AREA.contains(newPos.x, newPos.y) &&
		GAME_AREA.contains(newPos.x + 100, newPos.y + 100))
	{
		m_playerPos = newPos;
	}*/

	m_playerPos = newPos;
	m_currentFrame.setPosition(m_playerPos);
}

bool Player::isCollision(sf::Vector2f& playerPos)
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


	// TODO: pøidat reference na velikost dlaždice a rozmìry møížky
	const int tileSize = 128;

	int leftTile = std::max(0, (int)std::floor(playerBoxCollider.left / tileSize));
	int rightTile = std::min(10 - 1, (int)std::floor((playerBoxCollider.left + playerBoxCollider.width) / tileSize));
	int topTile = std::max(0, (int)std::floor(playerBoxCollider.top / tileSize));
	int bottomTile = std::min(6 - 1, (int)std::floor((playerBoxCollider.top + playerBoxCollider.height) / tileSize));

	for (int y = topTile; y <= bottomTile; ++y)
	{
		for (int x = leftTile; x <= rightTile; ++x)
		{
			if (!tileGrid[y][x].active)
				continue;

			if (playerBoxCollider.intersects(tileGrid[y][x].rect))
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

sf::Sprite& Player::getCurrentFrame()
{
	return m_currentFrame;
}