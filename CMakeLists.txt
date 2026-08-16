cmake_minimum_required(VERSION 3.20)

project(Aether
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(aether
    src/main.cpp
)

target_link_libraries(aether
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)