#include "aether/gameplay/player.hpp"

#include <cmath>
#include <algorithm>


#include "aether/collision/collision.hpp"

namespace aether::gameplay
{

Player::Player(sf::Vector2f position, float speed)
    : position_(position),
      speed_(speed)
{
    shape_.setRadius(20.0f);
    shape_.setOrigin({20.0f, 20.0f});
    shape_.setPosition(position_);
}

void Player::update(
    const input::InputState& input,
    float deltaTime,
    const world::World& world
)
{
    sf::Vector2f direction{0.0f, 0.0f};

    if (input.moveUp)
    {
        direction.y -= 1.0f;
    }

    if (input.moveDown)
    {
        direction.y += 1.0f;
    }

    if (input.moveLeft)
    {
        direction.x -= 1.0f;
    }

    if (input.moveRight)
    {
        direction.x += 1.0f;
    }

    if (direction.x != 0.0f || direction.y != 0.0f)
    {
        const float length = std::sqrt(
            direction.x * direction.x +
            direction.y * direction.y
        );

        direction /= length;
    }

    const sf::Vector2f movement =
        direction * speed_ * deltaTime;

    // Try horizontal movement first.
    sf::Vector2f newPosition = position_;
    newPosition.x += movement.x;

    if (!collidesWithWorld(newPosition, world))
    {
        position_.x = newPosition.x;
    }

    // Try vertical movement separately.
    newPosition = position_;
    newPosition.y += movement.y;

    if (!collidesWithWorld(newPosition, world))
    {
        position_.y = newPosition.y;
    }

    shape_.setPosition(position_);
}

bool Player::collidesWithWorld(
    sf::Vector2f position,
    const world::World& world
) const
{
    const float radius = shape_.getRadius();

    for (const auto& obstacle : world.getObstacles())
    {
        if (collision::circleIntersectsRectangle(
                position,
                radius,
                obstacle))
        {
            return true;
        }
    }

    return false;
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(shape_);
}

void Player::constrainToWorld(sf::Vector2f worldSize)
{
    const float radius = shape_.getRadius();

    position_.x = std::clamp(
        position_.x,
        radius,
        worldSize.x - radius
    );

    position_.y = std::clamp(
        position_.y,
        radius,
        worldSize.y - radius
    );

    shape_.setPosition(position_);
}

void Player::aimAt(sf::Vector2f worldPosition)
{
    const sf::Vector2f direction =
        worldPosition - position_;

    const float length =
        std::sqrt(
            direction.x * direction.x +
            direction.y * direction.y
        );

    if (length > 0.0001f)
    {
        aimDirection_ = {
            direction.x / length,
            direction.y / length
        };
    }
}

sf::Vector2f Player::getPosition() const
{
    return position_;
}

sf::Vector2f Player::getAimDirection() const
{
    return aimDirection_;
}

} // namespace aether::gameplay