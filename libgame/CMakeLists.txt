project(libgame)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11) 

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set (libgame_SRCS
    BitmapFont.h
    BitmapFont.cpp
    Engine.h
    Engine.cpp
    GameExceptions.h
    GameExceptions.cpp
    Rect.h
    Scene.h
    Scene.cpp
    Sprite.h
    Sprite.cpp
)

include_directories(${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_library (libgame ${libgame_SRCS})
