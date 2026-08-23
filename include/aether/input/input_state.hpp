#pragma once

#include <SFML/System/Vector2.hpp>

namespace aether::input
{

struct InputState
{
    bool moveUp{false};
    bool moveDown{false};
    bool moveLeft{false};
    bool moveRight{false};

    sf::Vector2i mousePosition{0, 0};
};

} // namespace aether::input