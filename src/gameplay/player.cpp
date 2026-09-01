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

    weapon_.setPosition(position_);
    weapon_.setDirection(aimDirection_);
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

    weapon_.setPosition(position_);
    weapon_.setDirection(aimDirection_);
    weapon_.update(deltaTime);
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
    // Draw player body.
    window.draw(shape_);

    // Draw weapon 
    weapon_.render(window);
    
    // Draw a visible line showing the current aim direction.
    const sf::Vector2f center = position_;

    const sf::Vector2f indicatorEnd =
        center + aimDirection_ * 60.0f;

    sf::Vertex indicator[] =
    {
        sf::Vertex{
            center,
            sf::Color::Red
        },

        sf::Vertex{
            indicatorEnd,
            sf::Color::Red
        }
    };

    window.draw(
        indicator,
        2,
        sf::PrimitiveType::Lines
    );
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

        weapon_.setDirection(aimDirection_);
    }
}

void Player::updateFacing()
{
    const float angle =
        std::atan2(aimDirection_.y, aimDirection_.x)
        * 180.0f / 3.14159265f;

    shape_.setRotation(sf::degrees(angle));
}


sf::Vector2f Player::getPosition() const
{
    return position_;
}

sf::Vector2f Player::getAimDirection() const
{
    return aimDirection_;
}

std::unique_ptr<Projectile> Player::fire()
{
    return weapon_.fire();
}

} // namespace aether::gameplay