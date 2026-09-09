#pragma once

namespace aether::gameplay
{

class Damageable
{
public:
    virtual ~Damageable() = default;

    virtual void takeDamage(float damage) = 0;
    virtual bool isAlive() const = 0;
};

} // namespace aether::gameplay