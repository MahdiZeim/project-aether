#include "aether/gameplay/projectile.hpp"

#include <cmath>

namespace aether::gameplay
{

Projectile::Projectile(
    sf::Vector2f position,
    sf::Vector2f direction,
    float speed,
    float damage,
    float maxRange
)
    : position_(position),
      direction_(direction),
      speed_(speed),
      damage_(damage),
      maxRange_(maxRange)
{
    const float length =
        std::sqrt(
            direction_.x * direction_.x +
            direction_.y * direction_.y
        );

    if (length > 0.0001f)
    {
        direction_ /= length;
    }

    shape_.setRadius(4.0f);
    shape_.setOrigin({4.0f, 4.0f});
    shape_.setPosition(position_);
}

void Projectile::update(float deltaTime)
{
    if (!alive_)
    {
        return;
    }

    const float distance =
        speed_ * deltaTime;

    position_ += direction_ * distance;

    distanceTraveled_ += distance;

    shape_.setPosition(position_);

    if (distanceTraveled_ >= maxRange_)
    {
        alive_ = false;
    }
}

void Projectile::render(sf::RenderWindow& window) const
{
    if (alive_)
    {
        window.draw(shape_);
    }
}

bool Projectile::isAlive() const
{
    return alive_;
}

sf::Vector2f Projectile::getPosition() const
{
    return position_;
}

} // namespace aether::gameplay