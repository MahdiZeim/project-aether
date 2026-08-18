#include "aether/rendering/camera.hpp"

#include <algorithm>

namespace aether::rendering
{

Camera::Camera(
    sf::Vector2f viewportSize,
    sf::Vector2f worldSize
)
    : worldSize_(worldSize)
{
    view_.setSize(viewportSize);
    view_.setCenter({
        worldSize.x / 2.0f,
        worldSize.y / 2.0f
    });
}

void Camera::follow(sf::Vector2f target)
{
    view_.setCenter(target);

    clampToWorld();
}

const sf::View& Camera::getView() const
{
    return view_;
}

void Camera::clampToWorld()
{
    const sf::Vector2f viewSize = view_.getSize();

    const float halfWidth = viewSize.x / 2.0f;
    const float halfHeight = viewSize.y / 2.0f;

    const float minX = halfWidth;
    const float maxX = worldSize_.x - halfWidth;

    const float minY = halfHeight;
    const float maxY = worldSize_.y - halfHeight;

    sf::Vector2f center = view_.getCenter();

    center.x = std::clamp(center.x, minX, maxX);
    center.y = std::clamp(center.y, minY, maxY);

    view_.setCenter(center);
}

} // namespace aether::rendering