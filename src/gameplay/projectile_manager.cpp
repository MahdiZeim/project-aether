#include "aether/gameplay/projectile_manager.hpp"

#include <algorithm>

namespace aether::gameplay
{

void ProjectileManager::add(
    std::unique_ptr<Projectile> projectile
)
{
    if (projectile)
    {
        projectiles_.push_back(std::move(projectile));
    }
}

void ProjectileManager::update(float deltaTime)
{
    for (auto& projectile : projectiles_)
    {
        projectile->update(deltaTime);
    }

    projectiles_.erase(
        std::remove_if(
            projectiles_.begin(),
            projectiles_.end(),
            [](const std::unique_ptr<Projectile>& projectile)
            {
                return !projectile->isAlive();
            }
        ),
        projectiles_.end()
    );
}

void ProjectileManager::render(
    sf::RenderWindow& window
) const
{
    for (const auto& projectile : projectiles_)
    {
        projectile->render(window);
    }
}

} // namespace aether::gameplay