cmake_minimum_required(VERSION 3.19)
project(3DGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(3DGame main.cpp
        GameEngine/WindowingSystem/Window.cpp GameEngine/WindowingSystem/Window.h
        GameEngine/Math/Vectors.h
        GameEngine/Math/Point.h
        GameEngine/Math/Matrix.h
        GameEngine/Math/Utils.h
        GameEngine/InputSystem/InputSystem.cpp GameEngine/InputSystem/InputSystem.h
        GameEngine/InputSystem/InputListener.h
        Game/MainGame.cpp Game/MainGame.h
        GameEngine/GraphicsEngine/Prerequisites.h
        GameEngine/GraphicsEngine/GraphicsEngine.cpp GameEngine/GraphicsEngine/GraphicsEngine.h
        GameEngine/GraphicsEngine/RenderSystem/RenderSystem.cpp GameEngine/GraphicsEngine/RenderSystem/RenderSystem.h
        GameEngine/GraphicsEngine/RenderSystem/SwapChain/SwapChain.cpp GameEngine/GraphicsEngine/RenderSystem/SwapChain/SwapChain.h
        GameEngine/GraphicsEngine/RenderSystem/DeviceContext/DeviceContext.cpp
        GameEngine/GraphicsEngine/RenderSystem/DeviceContext/DeviceContext.h)

target_link_libraries(3DGame ${CMAKE_SOURCE_DIR}/Libs/DirectXTex/bin/DirectXTexD.lib)

target_include_directories(3DGame PRIVATE Libs/DirectXTex/include)
target_include_directories(3DGame PRIVATE Libs/tinyobjloader/include)

set(LIBS d3d11 d3dcompiler)
target_link_libraries(3DGame ${LIBS})
