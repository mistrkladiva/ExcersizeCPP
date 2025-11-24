
#include <iostream>
#include <string>
#include <list>
#include <SFML/Graphics.hpp>

struct Character {
    std::string name;
	int frameRow = 0;
	int frameCol = 0;
    sf::IntRect textureArea;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Simple c++ dop-down game");

    sf::Texture charactestSpritesheet;
	if (!charactestSpritesheet.loadFromFile("assets/characters.png")) {
		std::cerr << "Error loading character spritesheet!" << std::endl;
        return 0;
    }

    Character playerSprt;
	playerSprt = { "Hero", 3, 3, sf::IntRect(0, 0, 100,100) };


    sf::Sprite sprite01;
    sprite01.setTexture(charactestSpritesheet);
    sprite01.setTextureRect(playerSprt.textureArea);
    sprite01.setPosition(200, 200);

    std::list<sf::Sprite> animation;

    for (int row = 0; row < playerSprt.frameRow; row++)
    {
        for (int col = 0; col < playerSprt.frameCol; col++)
        {
            sf::Sprite sprite;
            sprite.setTexture(charactestSpritesheet);
            sprite.setTextureRect(sf::IntRect(col*100, row*100, playerSprt.textureArea.width, playerSprt.textureArea.height) );
            sprite.setPosition((float)(col * 100), (float)(row * 100));
			animation.push_back(sprite);
        }
    }

    sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(sf::Vector2f(100.f, 100.f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(rect);
        window.draw(sprite01);

		for (sf::Sprite& sprite : animation) {
            window.draw(sprite);
        }

        window.display();
    }
}
