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
	m_textObject.setCharacterSize(24); // in pixels, not points!
	m_textObject.setFillColor(sf::Color::Red);

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
	m_durationSeconds = seconds;
	m_dialogueClock.restart();
	m_isActive = true;
}

void DialogueManager::setDialoguePosition(sf::Vector2f position)
{
	m_background.setPosition(position);
	m_textObject.setPosition(position.x + 10.f, position.y + 10.f);
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

	float textWidth = m_textObject.getLocalBounds().width + 20;
	float textHeight = m_textObject.getLocalBounds().height + 20;

	m_textObject.setOrigin(textWidth / 2, textHeight / 2);
	m_background.setOrigin(textWidth / 2, textHeight / 2);

	m_background.setSize(sf::Vector2f(textWidth, textHeight));
	m_window->draw(m_background);
	m_window->draw(m_textObject);
}