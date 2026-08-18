#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

namespace aether::rendering
{

class Camera
{
public:
    Camera(
        sf::Vector2f viewportSize,
        sf::Vector2f worldSize
    );

    void follow(sf::Vector2f target);

    const sf::View& getView() const;

private:
    void clampToWorld();

    sf::View view_;
    sf::Vector2f worldSize_;
};

} // namespace aether::rendering