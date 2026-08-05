cmake_minimum_required(VERSION 3.20)
project(EngineTest CXX C)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

add_executable(gameengine 
            src/main.cpp
            src/glad.c
            src/mesh_loader.cpp
            src/mesh.cpp
            src/object.cpp
            src/stb_image.cpp
            src/shader.cpp
            src/camera.cpp
            src/action.cpp
            src/scene.cpp
            )

target_link_libraries(gameengine PRIVATE OpenGL::GL glfw dl assimp)
target_include_directories(gameengine PRIVATE include)