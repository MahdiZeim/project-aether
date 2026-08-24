#include <iostream>
#include <SFML/Graphics.hpp>

#include "aether/gameplay/player.hpp"
#include "aether/input/input_state.hpp"
#include "aether/world/world.hpp"
#include "aether/rendering/camera.hpp"
#include "aether/rendering/world_renderer.hpp"

int main()
{
    constexpr float windowWidth = 1280.0f;
    constexpr float windowHeight = 720.0f;

    constexpr float worldWidth = 3000.0f;
    constexpr float worldHeight = 2000.0f;

    sf::RenderWindow window(
        sf::VideoMode({
            static_cast<unsigned int>(windowWidth),
            static_cast<unsigned int>(windowHeight)
        }),
        "Project Aether"
    );

    window.setFramerateLimit(144);

    aether::world::World world(
        worldWidth,
        worldHeight
    );

    aether::rendering::Camera camera(
        {windowWidth, windowHeight},
        world.getSize()
    );

    aether::rendering::WorldRenderer worldRenderer(world);

    aether::gameplay::Player player(
        {worldWidth / 2.0f, worldHeight / 2.0f},
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

        input.mousePosition = sf::Mouse::getPosition(window);

        const sf::Vector2f mouseWorldPosition =
            window.mapPixelToCoords(input.mousePosition);

        player.aimAt(mouseWorldPosition);

        player.updateFacing();
        
            std::cout
            << "Mouse World: "
            << mouseWorldPosition.x
            << ", "
            << mouseWorldPosition.y
            << '\n';


        input.moveUp =
            sf::Keyboard::isKeyPressed(
                sf::Keyboard::Key::W
            );

        input.moveDown =
            sf::Keyboard::isKeyPressed(
                sf::Keyboard::Key::S
            );

        input.moveLeft =
            sf::Keyboard::isKeyPressed(
                sf::Keyboard::Key::A
            );

        input.moveRight =
            sf::Keyboard::isKeyPressed(
                sf::Keyboard::Key::D
            );


        player.update(
            input,
            deltaTime,
            world
        );

        player.constrainToWorld(world.getSize());

        camera.follow(player.getPosition());

        window.setView(camera.getView());

        window.clear(sf::Color(20, 20, 25));

        worldRenderer.render(window);

        player.render(window);

        window.display();
    }

    return 0;
}