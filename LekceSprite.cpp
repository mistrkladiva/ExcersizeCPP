
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    std::cout << "Hello World!\n";

    sf::RenderWindow window(sf::VideoMode(1024, 768), "game");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));
        rect.setFillColor(sf::Color::Red);
        rect.setPosition(sf::Vector2f(100.f, 100.f));

        window.clear(sf::Color::Black);
        window.draw(rect);

        window.display();
    }
}
