#include "aether/world/world.hpp"

namespace aether::world
{

World::World(float width, float height)
    : size_(width, height)
{
    obstacles_.emplace_back(
        sf::Vector2f{500.0f, 400.0f},
        sf::Vector2f{300.0f, 220.0f}
    );

    obstacles_.emplace_back(
        sf::Vector2f{1700.0f, 700.0f},
        sf::Vector2f{450.0f, 250.0f}
    );

    obstacles_.emplace_back(
        sf::Vector2f{2300.0f, 300.0f},
        sf::Vector2f{160.0f, 120.0f}
    );
}

sf::Vector2f World::getSize() const
{
    return size_;
}

const std::vector<sf::FloatRect>& World::getObstacles() const
{
    return obstacles_;
}

} // namespace aether::world