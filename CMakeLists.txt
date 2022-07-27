project(GFX)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/${BUILD_DIR_POSTFIX} CACHE STRING
    "Do not change this setting."
    FORCE)

add_subdirectory(libgame)

add_subdirectory(dirt)
add_subdirectory(joysticktest)
add_subdirectory(ratrace)
add_subdirectory(sprites)
add_subdirectory(tetris)
add_subdirectory(tilemap)
add_subdirectory(ttf2png)
