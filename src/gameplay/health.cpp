#include "aether/gameplay/health.hpp"

#include <algorithm>

namespace aether::gameplay
{

Health::Health(float maxHealth)
    : maxHealth_(maxHealth),
      currentHealth_(maxHealth)
{
}

void Health::takeDamage(float damage)
{
    if (damage <= 0.0f)
    {
        return;
    }

    currentHealth_ = std::max(
        0.0f,
        currentHealth_ - damage
    );
}

float Health::getCurrent() const
{
    return currentHealth_;
}

float Health::getMax() const
{
    return maxHealth_;
}

bool Health::isAlive() const
{
    return currentHealth_ > 0.0f;
}

} // namespace aether::gameplay