#include "aether/gameplay/player.hpp"
#include <cmath>

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

void Player::update(const input::InputState& input, float deltaTime)
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
        float length = std::sqrt(
            direction.x * direction.x +
            direction.y * direction.y
        );

        direction /= length;
    }

    position_ += direction * speed_ * deltaTime;

    shape_.setPosition(position_);
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(shape_);
}

sf::Vector2f Player::getPosition() const
{
    return position_;
}

} // namespace aether::gameplay