#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class DialogueManager
{
	public:
		DialogueManager(sf::RenderWindow* window);
		void draw();
		void setDialogueMessage(const std::string& message);
		void setDialogueMessage(const std::string& message, float seconds);
		void setDialoguePosition(sf::Vector2f position);
		bool isDialogueActive() const { return m_isActive; }

private:
	sf::RenderWindow* m_window;
	sf::Font m_font;
	std::string m_text;
	sf::Text m_textObject;
	sf::RectangleShape m_background;


	void setTextObject();

	// nové členy pro řízení zobrazení dialogu
	bool m_isActive = false;
	sf::Clock m_dialogueClock;
	float m_durationSeconds = 3.f; // výchozí doba zobrazení v sekundách
};
