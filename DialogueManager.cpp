#include "DialogueManager.h"

DialogueManager::DialogueManager(sf::RenderWindow* window)
	: m_window(window)
{
	setTextObject();
}

void DialogueManager::setTextObject()
{
	if (!m_font.loadFromFile("assets/fonts/arial.ttf"))
	{
		std::cerr << "Error loading font!" << std::endl;
	}

	m_textObject.setFont(m_font);
	m_textObject.setCharacterSize(24);
	m_textObject.setFillColor(sf::Color::White);

	m_textObject.setStyle(sf::Text::Bold);
	m_background.setFillColor(sf::Color(0, 0, 0, 150));
}

void DialogueManager::setDialogueMessage(const std::string& message)
{
	setDialogueMessage(message, m_durationSeconds);
}

void DialogueManager::setDialogueMessage(const std::string& message, float seconds)
{
	m_textObject.setString(sf::String::fromUtf8(message.begin(), message.end()));

	float textWidth = m_textObject.getLocalBounds().width;
	float textHeight = m_textObject.getLocalBounds().height;
	float backgroundOffset = 40.f;

	m_background.setSize(sf::Vector2f((textWidth + backgroundOffset), (textHeight + backgroundOffset)));

	m_textObject.setOrigin(textWidth / 2, textHeight / 2);
	m_background.setOrigin((textWidth + backgroundOffset) / 2, (textHeight + backgroundOffset) / 2);

	m_durationSeconds = seconds;
	m_dialogueClock.restart();
	m_isActive = true;
}

void DialogueManager::setDialoguePosition(sf::Vector2f position)
{
	m_background.setPosition(position);
	m_textObject.setPosition(position.x, position.y - 5);
}

void DialogueManager::draw()
{
	if (!m_isActive)
		return;

	// pokud čas vypršel, deaktivuj dialog
	if (m_dialogueClock.getElapsedTime().asSeconds() >= m_durationSeconds)
	{
		m_isActive = false;
		return;
	}

	m_window->draw(m_background);
	m_window->draw(m_textObject);
}