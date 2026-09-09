#pragma once

#include "aether/gameplay/damageable.hpp"

namespace aether::gameplay
{

class Health : public Damageable
{
public:
    explicit Health(float maxHealth);

    void takeDamage(float damage) override;

    float getCurrent() const;
    float getMax() const;

    bool isAlive() const override;

private:
    float maxHealth_;
    float currentHealth_;
};

} // namespace aether::gameplay