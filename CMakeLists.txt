cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(untitled
        main.cpp
        Cell.cpp
        Cell.h
        SkinProblem.cpp
        SkinProblem.h
        Board.cpp
        Board.h
        Infected.cpp
        Infected.h
        Immune.cpp
        Immune.h
        Run.h
        Run.cpp
)

# ZMIANA: 'PRIVATE' wielkimi literami
target_link_libraries(untitled PRIVATE sfml-graphics sfml-window sfml-system)