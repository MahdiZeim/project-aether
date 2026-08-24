#pragma once

#include <SFML/Graphics.hpp>

namespace aether::gameplay
{

class Weapon
{
public:
    Weapon();

    void setPosition(sf::Vector2f position);
    void setDirection(sf::Vector2f direction);

    void render(sf::RenderWindow& window) const;

private:
    sf::RectangleShape shape_;
    sf::Vector2f position_{0.0f, 0.0f};
    sf::Vector2f direction_{1.0f, 0.0f};
};

} // namespace aether::gameplay