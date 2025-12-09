cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        Cell.cpp
        Cell.h
        SkinProblem.cpp
        SkinProblem.h
        Board.cpp
        Board.h
        Infected.cpp
        Infected.h
)
