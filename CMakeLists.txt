cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
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