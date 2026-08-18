#include "aether/rendering/world_renderer.hpp"

namespace aether::rendering
{

WorldRenderer::WorldRenderer(const world::World& world)
    : world_(world)
{
    const sf::Vector2f worldSize = world_.getSize();

    background_.setSize(worldSize);
    background_.setPosition({0.0f, 0.0f});
    background_.setFillColor(sf::Color(35, 40, 45));
}

void WorldRenderer::render(sf::RenderWindow& window)
{
    renderGround(window);
    renderGrid(window);
    renderObstacles(window);
}

void WorldRenderer::renderGround(sf::RenderWindow& window)
{
    window.draw(background_);
}

void WorldRenderer::renderGrid(sf::RenderWindow& window)
{
    constexpr float gridSize = 100.0f;

    const sf::Vector2f worldSize = world_.getSize();

    sf::VertexArray lines(sf::PrimitiveType::Lines);

    for (float x = 0.0f; x <= worldSize.x; x += gridSize)
    {
        sf::Vertex top;
        top.position = {x, 0.0f};
        top.color = sf::Color(55, 60, 65);

        sf::Vertex bottom;
        bottom.position = {x, worldSize.y};
        bottom.color = sf::Color(55, 60, 65);

        lines.append(top);
        lines.append(bottom);
    }

    for (float y = 0.0f; y <= worldSize.y; y += gridSize)
    {
        sf::Vertex left;
        left.position = {0.0f, y};
        left.color = sf::Color(55, 60, 65);

        sf::Vertex right;
        right.position = {worldSize.x, y};
        right.color = sf::Color(55, 60, 65);

        lines.append(left);
        lines.append(right);
    }

    window.draw(lines);
}

void WorldRenderer::renderObstacles(sf::RenderWindow& window)
{
    for (const auto& obstacle : world_.getObstacles())
    {
        sf::RectangleShape shape;

        shape.setPosition(obstacle.position);
        shape.setSize(obstacle.size);
        shape.setFillColor(sf::Color(80, 85, 90));

        window.draw(shape);
    }
}

} // namespace aether::rendering