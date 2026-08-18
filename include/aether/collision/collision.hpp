#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace aether::collision
{

bool circleIntersectsRectangle(
    sf::Vector2f circleCenter,
    float radius,
    const sf::FloatRect& rectangle
);

} // namespace aether::collision