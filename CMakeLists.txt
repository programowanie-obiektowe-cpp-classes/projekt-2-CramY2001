cmake_minimum_required(VERSION 3.29)
project(Projekt2)

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR "C:/SMFL/SFML-2.5.1/lib/cmake/SFML") # Dostosuj ścieżkę do lokalizacji SFML na twoim komputerze
add_executable(Projekt2 main.cpp
        Projectile.h
        Enemy.h
        Player.h
        Game.h
        Game.cpp
        Player.cpp
        Enemy.cpp
        Projectile.cpp)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(Projekt2 sfml-graphics sfml-window sfml-system)