#include <SFML/Graphics.hpp>

#include "aether/gameplay/player.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1280, 720}),
        "Project Aether"
    );

    window.setFramerateLimit(144);

    aether::gameplay::Player player(
        {640.0f, 360.0f},
        300.0f
    );

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        const float deltaTime = clock.restart().asSeconds();

        aether::input::InputState input;

        input.moveUp =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);

        input.moveDown =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);

        input.moveLeft =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);

        input.moveRight =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

        player.update(input, deltaTime);

        window.clear(sf::Color(20, 20, 25));

        player.render(window);

        window.display();
    }

    return 0;
}