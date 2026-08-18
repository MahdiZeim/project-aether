#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

namespace aether::world
{

class World
{
public:
    World(float width, float height);

    sf::Vector2f getSize() const;

    const std::vector<sf::FloatRect>& getObstacles() const;

private:
    sf::Vector2f size_;
    std::vector<sf::FloatRect> obstacles_;
};

} // namespace aether::world