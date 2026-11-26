cmake_minimum_required(VERSION 3.28)
project(Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(game src/main.cpp src/game.cpp src/player.cpp src/sword.cpp src/staff.cpp src/aura.cpp)
target_compile_definitions(game PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets/")
target_link_libraries(game PRIVATE SFML::Graphics)