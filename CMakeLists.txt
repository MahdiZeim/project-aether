cmake_minimum_required(VERSION 3.20)

project(ProjectAether
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 COMPONENTS
    Graphics
    Window
    System
    REQUIRED
)

# ============================================================
# Main game
# ============================================================

add_executable(aether
    src/main.cpp
    src/gameplay/player.cpp
    src/world/world.cpp
    src/rendering/camera.cpp
    src/rendering/world_renderer.cpp
    src/collision/collision.cpp
    src/gameplay/weapon.cpp
)

target_include_directories(aether PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(aether PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# ============================================================
# Collision tests
# ============================================================

add_executable(aether_collision_tests
    tests/collision/collision_tests.cpp
    src/collision/collision.cpp
)

target_include_directories(aether_collision_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(aether_collision_tests PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)