#include <iostream>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "aether/collision/collision.hpp"

namespace
{

int testsPassed = 0;
int testsFailed = 0;

void expectTrue(bool condition, const char* testName)
{
    if (condition)
    {
        ++testsPassed;
        std::cout << "[PASS] " << testName << '\n';
    }
    else
    {
        ++testsFailed;
        std::cout << "[FAIL] " << testName << '\n';
    }
}

void expectFalse(bool condition, const char* testName)
{
    expectTrue(!condition, testName);
}

} // namespace

int main()
{
    const sf::FloatRect rectangle{
        {100.0f, 100.0f},
        {200.0f, 100.0f}
    };

    // 1. Circle completely outside.
    expectFalse(
        aether::collision::circleIntersectsRectangle(
            {50.0f, 50.0f},
            20.0f,
            rectangle
        ),
        "Circle completely outside"
    );

    // 2. Circle completely inside.
    expectTrue(
        aether::collision::circleIntersectsRectangle(
            {200.0f, 150.0f},
            20.0f,
            rectangle
        ),
        "Circle completely inside"
    );

    // 3. Circle touching the left edge.
    expectTrue(
        aether::collision::circleIntersectsRectangle(
            {80.0f, 150.0f},
            20.0f,
            rectangle
        ),
        "Circle touching left edge"
    );

    // 4. Circle intersecting the top edge.
    expectTrue(
        aether::collision::circleIntersectsRectangle(
            {200.0f, 80.0f},
            20.0f,
            rectangle
        ),
        "Circle intersecting top edge"
    );

    // 5. Circle intersecting a corner.
    expectTrue(
        aether::collision::circleIntersectsRectangle(
            {85.0f, 85.0f},
            25.0f,
            rectangle
        ),
        "Circle intersecting corner"
    );

    // 6. Circle close to corner but not touching.
    expectFalse(
        aether::collision::circleIntersectsRectangle(
            {70.0f, 70.0f},
            20.0f,
            rectangle
        ),
        "Circle outside near corner"
    );

    // 7. Circle far away.
    expectFalse(
        aether::collision::circleIntersectsRectangle(
            {1000.0f, 1000.0f},
            20.0f,
            rectangle
        ),
        "Circle far away"
    );

    std::cout << '\n';
    std::cout << "Tests passed: " << testsPassed << '\n';
    std::cout << "Tests failed: " << testsFailed << '\n';

    return testsFailed == 0 ? 0 : 1;
}