cmake_minimum_required(VERSION 3.24)
project(auto)

set(CMAKE_CXX_STANDARD 20)


add_executable(MealyMachine
        main.cpp
        transition/Transition.cpp
        machines/MealyMachine.cpp
        machines/MooreMachine.cpp
        )

add_executable(M machines/spare.cpp)