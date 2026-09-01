#pragma once

#include <SFML/Graphics.hpp>

namespace aether::gameplay
{

class Projectile
{
public:
    Projectile(
        sf::Vector2f position,
        sf::Vector2f direction,
        float speed,
        float damage,
        float maxRange
    );

    void update(float deltaTime);

    void render(sf::RenderWindow& window) const;

    bool isAlive() const;

    sf::Vector2f getPosition() const;

private:
    sf::CircleShape shape_;

    sf::Vector2f position_;
    sf::Vector2f direction_;

    float speed_;
    float damage_;
    float maxRange_;

    float distanceTraveled_{0.0f};
    bool alive_{true};
};

} // namespace aether::gameplay