cmake_minimum_required(VERSION 3.19)
project(3DGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(3DGame main.cpp GameEngine/WindowingSystem/Window.cpp GameEngine/WindowingSystem/Window.h)