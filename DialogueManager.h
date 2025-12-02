#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class DialogueManager
{
	public:
		DialogueManager(sf::RenderWindow* window);
		void draw();
		void setDialogueMessage(const std::string& message);
		void setDialoguePosition(sf::Vector2f position);

private:
	sf::RenderWindow* m_window;
	sf::Font m_font;
	std::string m_text;
	sf::Text m_textObject;
	sf::RectangleShape m_background;

	void setTextObject();
	
};

