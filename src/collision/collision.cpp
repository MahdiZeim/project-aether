#include "aether/collision/collision.hpp"

#include <algorithm>

namespace aether::collision
{

bool circleIntersectsRectangle(
    sf::Vector2f circleCenter,
    float radius,
    const sf::FloatRect& rectangle
)
{
    const float closestX = std::clamp(
        circleCenter.x,
        rectangle.position.x,
        rectangle.position.x + rectangle.size.x
    );

    const float closestY = std::clamp(
        circleCenter.y,
        rectangle.position.y,
        rectangle.position.y + rectangle.size.y
    );

    const float dx = circleCenter.x - closestX;
    const float dy = circleCenter.y - closestY;

    const float distanceSquared = dx * dx + dy * dy;

    return distanceSquared <= radius * radius;
}

} // namespace aether::collision