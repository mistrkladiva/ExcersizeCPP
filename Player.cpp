#include "Player.h"

Player::Player(sf::RenderWindow* window, sf::Texture& spritesheet, SpriteCharacter& sprt)
{
	m_window = window;
	m_spritesheet = spritesheet;
	m_sprt = sprt;
	loadCharacterSprites();
	// clock už je implicitnì spuštìný pøi vytvoøení
	m_timeAccumulator = sf::Time::Zero;
	m_currentFrameIndex = 0;
	m_lastDirection = -2;
}

void Player::update(int direction, sf::Vector2f deltaPos)
{
	if (direction >= 0) {
		// pokud je smìr mimo rozsah, nastav na idle
		if ((direction * m_sprt.frameCol) + m_sprt.frameCol > m_animation.size()) {
			direction = -1;
		}

		// pokud se zmìnil smìr, resetujeme index a akumulátor èasu
		if (direction != m_lastDirection) {
			m_currentFrameIndex = 0;
			m_timeAccumulator = sf::Time::Zero;
			m_lastDirection = direction;
		}

		// vytvoøí nový vektor z vektoru animaèních polí podle øádku (øádek má snímky pohybu podle smìru
		m_currentAnimationRow.clear();
		m_currentAnimationRow.assign(
			m_animation.begin() + (direction * m_sprt.frameCol),
			m_animation.begin() + (direction * m_sprt.frameCol) + m_sprt.frameCol
		);

		animation();
		move(deltaPos);
	}
}

void Player::draw()
{
	// vykreslíme všechny snímky pro kontrolu naètení
	for (auto& frame : m_animation)
	{
		m_window->draw(frame);
	}

	m_window->draw(m_currentFrame);
}

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

void Player::loadCharacterSprites()
{

	int textureX;
	int textureY;

	for (int row = 0; row < m_sprt.frameRow; row++)
	{
		for (int col = 0; col < m_sprt.frameCol; col++)
		{
			textureX = col * m_sprt.textureArea.width + m_sprt.textureArea.left;
			textureY = row * m_sprt.textureArea.height + m_sprt.textureArea.top;

			m_sprite.setTexture(m_spritesheet);
			m_sprite.setTextureRect(sf::IntRect(textureX, textureY, m_sprt.textureArea.width, m_sprt.textureArea.height));
			// setPosition jen pro vykreslení celého setu ke kontrole
			m_sprite.setPosition((float)(col * m_sprt.textureArea.width), (float)(row * m_sprt.textureArea.height));
			m_animation.push_back(m_sprite);
		}
	}
}

void Player::animation()
{
	// pøidáme uplynulý èas
	m_timeAccumulator += m_clock.restart();

	// když uplyne dost èasu, pøepneme na další snímek
	if (m_timeAccumulator.asSeconds() >= m_frameDuration && !m_currentAnimationRow.empty()) {
		// odeèteme pøesný krok (umožní stabilnìjší tempo i když frame drop)
		m_timeAccumulator -= sf::seconds(m_frameDuration);
		m_currentFrameIndex = (m_currentFrameIndex + 1) % (int)m_currentAnimationRow.size();
	}

	int idx = m_currentFrameIndex % (int)m_currentAnimationRow.size();

	m_currentFrame = m_currentAnimationRow[idx];

}
