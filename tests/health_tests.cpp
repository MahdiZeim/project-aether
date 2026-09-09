#include <iostream>

#include "aether/gameplay/health.hpp"

int main()
{
    int passed = 0;
    int failed = 0;

    auto check = [&](const char* name, bool condition)
    {
        if (condition)
        {
            std::cout << "[PASS] " << name << '\n';
            ++passed;
        }
        else
        {
            std::cout << "[FAIL] " << name << '\n';
            ++failed;
        }
    };

    // Test 1: Initial health
    {
        aether::gameplay::Health health(100.0f);

        check(
            "Initial current health",
            health.getCurrent() == 100.0f
        );

        check(
            "Initial max health",
            health.getMax() == 100.0f
        );

        check(
            "Initial state is alive",
            health.isAlive()
        );
    }

    // Test 2: Damage
    {
        aether::gameplay::Health health(100.0f);

        health.takeDamage(25.0f);

        check(
            "Health decreases after damage",
            health.getCurrent() == 75.0f
        );

        check(
            "Entity remains alive after partial damage",
            health.isAlive()
        );
    }

    // Test 3: Multiple damage
    {
        aether::gameplay::Health health(100.0f);

        health.takeDamage(30.0f);
        health.takeDamage(20.0f);

        check(
            "Multiple damage applications",
            health.getCurrent() == 50.0f
        );
    }

    // Test 4: Lethal damage
    {
        aether::gameplay::Health health(100.0f);

        health.takeDamage(100.0f);

        check(
            "Health reaches zero",
            health.getCurrent() == 0.0f
        );

        check(
            "Entity becomes dead",
            !health.isAlive()
        );
    }

    // Test 5: Damage greater than health
    {
        aether::gameplay::Health health(100.0f);

        health.takeDamage(150.0f);

        check(
            "Health never becomes negative",
            health.getCurrent() == 0.0f
        );

        check(
            "Entity remains dead",
            !health.isAlive()
        );
    }

    // Test 6: Zero damage
    {
        aether::gameplay::Health health(100.0f);

        health.takeDamage(0.0f);

        check(
            "Zero damage has no effect",
            health.getCurrent() == 100.0f
        );
    }

    // Test 7: Negative damage
    {
        aether::gameplay::Health health(100.0f);

        health.takeDamage(-25.0f);

        check(
            "Negative damage has no effect",
            health.getCurrent() == 100.0f
        );
    }

        // Test 8: Damageable abstraction
    {
        aether::gameplay::Health health(100.0f);

        aether::gameplay::Damageable& damageable = health;

        damageable.takeDamage(40.0f);

        check(
            "Damageable applies damage",
            health.getCurrent() == 60.0f
        );

        check(
            "Damageable reports alive state",
            damageable.isAlive()
        );
    }
    
    std::cout << '\n';
    std::cout << "Tests passed: " << passed << '\n';
    std::cout << "Tests failed: " << failed << '\n';

    return failed == 0 ? 0 : 1;
}