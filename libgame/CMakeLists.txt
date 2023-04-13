project(libgame)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11) 

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB SDL_DLLS ${SDL2_LIBRARY_DIR}/*.dll)
file(GLOB SDL_IMAGE_DLLS ${SDL2_IMAGE_LIBRARY_DIR}/*.dll)

set (libgame_SRCS
    BitmapFont.h
    BitmapFont.cpp
    EngineInterface.h
    Engine.h
    Engine.cpp
    GameExceptions.h
    GameExceptions.cpp
    Path.h
    Path.cpp
    Rect.h
    Scene.h
    Scene.cpp
    Sprite.h
    Sprite.cpp
)

include_directories(${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_library (libgame ${libgame_SRCS})

if(WIN32)
    add_custom_command(TARGET libgame POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL_DLLS} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    add_custom_command(TARGET libgame POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL_IMAGE_DLLS} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif(WIN32)
