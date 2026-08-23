#pragma once

#include <SFML/Graphics.hpp>

#include "aether/input/input_state.hpp"
#include "aether/world/world.hpp"

namespace aether::gameplay
{

class Player
{
public:
    Player(sf::Vector2f position, float speed);

    void update(
        const input::InputState& input,
        float deltaTime,
        const world::World& world
    );

    void render(sf::RenderWindow& window);

    void constrainToWorld(sf::Vector2f worldSize);

    void aimAt(sf::Vector2f worldPosition);

    sf::Vector2f getPosition() const;

    sf::Vector2f getAimDirection() const;

private:
    bool collidesWithWorld(
        sf::Vector2f position,
        const world::World& world
    ) const;

    sf::Vector2f position_;
    float speed_;

    sf::Vector2f aimDirection_{1.0f, 0.0f};
    
    sf::CircleShape shape_;
};

} // namespace aether::gameplay