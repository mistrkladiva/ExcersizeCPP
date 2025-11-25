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
	if (direction == -1)
		return;

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
	// vykreslíme všechny snímky pro kontrolu naètení
	/*for (auto& frame : m_animation)
	{
		m_window->draw(frame);
	}*/

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

	if (GAME_AREA.contains(newPos.x, newPos.y) &&
		GAME_AREA.contains(newPos.x + 100, newPos.y + 100))
	{
		m_playerPos = newPos;
	}

	m_currentFrame.setPosition(m_playerPos);
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
			int x = col * m_sprt.textureSize.width + m_sprt.textureSize.left;
			int y = row * m_sprt.textureSize.height + m_sprt.textureSize.top;

			sf::Sprite spr;
			spr.setTexture(m_spritesheet);
			spr.setTextureRect(sf::IntRect(x, y, m_sprt.textureSize.width, m_sprt.textureSize.height));

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
