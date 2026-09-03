#include "aether/gameplay/weapon.hpp"

#include <cmath>

namespace aether::gameplay
{

Weapon::Weapon()
{
    shape_.setSize({30.0f, 8.0f});
    shape_.setOrigin({0.0f, 4.0f});
}

void Weapon::setPosition(sf::Vector2f position)
{
    position_ = position;
    shape_.setPosition(position_);
}

void Weapon::setDirection(sf::Vector2f direction)
{
    const float length =
        std::sqrt(
            direction.x * direction.x +
            direction.y * direction.y
        );

    if (length <= 0.0001f)
    {
        return;
    }

    direction_ = {
        direction.x / length,
        direction.y / length
    };

    const float angle =
        std::atan2(direction_.y, direction_.x)
        * 180.0f / 3.14159265f;

    shape_.setRotation(sf::degrees(angle));
}

void Weapon::render(sf::RenderWindow& window) const
{
    window.draw(shape_);
}

void Weapon::update(float deltaTime)
{
    if (fireCooldown_ > 0.0f)
    {
        fireCooldown_ -= deltaTime;

        if (fireCooldown_ < 0.0f)
        {
            fireCooldown_ = 0.0f;
        }
    }
}

std::unique_ptr<Projectile> Weapon::fire()
{
    if (ammo_ <= 0)
    {
        return nullptr;
    }

    if (fireCooldown_ > 0.0f)
    {
        return nullptr;
    }

    fireCooldown_ = 1.0f / fireRate_;

    --ammo_;

    return std::make_unique<Projectile>(
        position_,
        direction_,
        projectileSpeed_,
        damage_,
        range_
    );
}

int Weapon::getAmmo() const
{
    return ammo_;
}

int Weapon::getMagazineSize() const
{
    return magazineSize_;
}

} // namespace aether::gameplay