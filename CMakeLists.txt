cmake_minimum_required(VERSION 3.19)
project(3DGame)

set(CMAKE_CXX_STANDARD 17)

target_link_libraries(3DGame ${CMAKE_SOURCE_DIR}/Libs/DirectXTex/bin/DirectXTexD.lib)

set(LIBS d3d11 d3dcompiler)
target_link_libraries(3DGame ${LIBS})

add_executable(3DGame main.cpp
        GameEngine/WindowingSystem/Window.cpp GameEngine/WindowingSystem/Window.h
        GameEngine/Math/Vectors.h
        GameEngine/Math/Point.h
        GameEngine/Math/Matrix.h
        GameEngine/Math/Utils.h
        GameEngine/InputSystem/InputSystem.cpp GameEngine/InputSystem/InputSystem.h
        GameEngine/InputSystem/InputListener.h
        Game/MainGame.cpp Game/MainGame.h)
