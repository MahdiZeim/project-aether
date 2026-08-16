#pragma once

#include <SFML/Graphics.hpp>
#include "aether/input/input_state.hpp"

namespace aether::gameplay
{

class Player
{
public:
    Player(sf::Vector2f position, float speed);

    void update(
    const input::InputState& input,
    float deltaTime
    );
    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

private:
    sf::Vector2f position_;
    float speed_;

    sf::CircleShape shape_;
};

} // namespace aether::gameplay