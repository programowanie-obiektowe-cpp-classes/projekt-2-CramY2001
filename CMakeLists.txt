cmake_minimum_required(VERSION 3.29)
project(projekt-2-CramY2001)

set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_SOURCE_DIR}/include)
set(SFML_DIR "C:/SMFL/SFML-2.5.1/lib/cmake/SFML") # Dostosuj ścieżkę do lokalizacji SFML na twoim komputerze
add_executable(projekt-2-CramY2001
        src/main.cpp
        src/Game.cpp
        src/Player.cpp
        src/Enemy.cpp
        src/Projectile.cpp
        src/Projectile.cpp
)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(projekt-2-CramY2001 sfml-graphics sfml-window sfml-system)