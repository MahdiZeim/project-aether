#pragma once

#include <SFML/Graphics.hpp>

#include "aether/world/world.hpp"

namespace aether::rendering
{

class WorldRenderer
{
public:
    explicit WorldRenderer(const world::World& world);

    void render(sf::RenderWindow& window);

private:
    void renderGround(sf::RenderWindow& window);
    void renderGrid(sf::RenderWindow& window);
    void renderObstacles(sf::RenderWindow& window);

    const world::World& world_;

    sf::RectangleShape background_;
};

} // namespace aether::rendering