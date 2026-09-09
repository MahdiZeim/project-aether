#pragma once

namespace aether::gameplay
{

class Health
{
public:
    explicit Health(float maxHealth);

    void takeDamage(float damage);

    float getCurrent() const;
    float getMax() const;

    bool isAlive() const;

private:
    float maxHealth_;
    float currentHealth_;
};

} // namespace aether::gameplay