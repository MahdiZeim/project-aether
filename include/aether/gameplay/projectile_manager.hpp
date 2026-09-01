#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "aether/gameplay/projectile.hpp"

namespace aether::gameplay
{

class ProjectileManager
{
public:
    void add(std::unique_ptr<Projectile> projectile);

    void update(float deltaTime);

    void render(sf::RenderWindow& window) const;

private:
    std::vector<std::unique_ptr<Projectile>> projectiles_;
};

} // namespace aether::gameplay