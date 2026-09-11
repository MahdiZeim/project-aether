#include <iostream>

#include "aether/gameplay/player.hpp"

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

    // Test 1: Initial player health
    {
        aether::gameplay::Player player(
            {100.0f, 100.0f},
            200.0f
        );

        check(
            "Player starts with full health",
            player.getHealth() == 100.0f
        );

        check(
            "Player max health is correct",
            player.getMaxHealth() == 100.0f
        );

        check(
            "Player starts alive",
            player.isAlive()
        );
    }

    // Test 2: Player takes damage
    {
        aether::gameplay::Player player(
            {100.0f, 100.0f},
            200.0f
        );

        player.takeDamage(25.0f);

        check(
            "Player health decreases after damage",
            player.getHealth() == 75.0f
        );

        check(
            "Player remains alive after damage",
            player.isAlive()
        );
    }

    // Test 3: Lethal damage
    {
        aether::gameplay::Player player(
            {100.0f, 100.0f},
            200.0f
        );

        player.takeDamage(100.0f);

        check(
            "Player health reaches zero",
            player.getHealth() == 0.0f
        );

        check(
            "Player becomes dead",
            !player.isAlive()
        );
    }

    // Test 4: Excessive damage
    {
        aether::gameplay::Player player(
            {100.0f, 100.0f},
            200.0f
        );

        player.takeDamage(150.0f);

        check(
            "Player health never becomes negative",
            player.getHealth() == 0.0f
        );

        check(
            "Player remains dead after excessive damage",
            !player.isAlive()
        );
    }

    std::cout << '\n';
    std::cout << "Tests passed: " << passed << '\n';
    std::cout << "Tests failed: " << failed << '\n';

    return failed == 0 ? 0 : 1;
}