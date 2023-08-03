project(maze)

cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 11) 

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
file(GLOB SDL_DLLS ${SDL2_LIBRARY_DIR}/*.dll)
file(GLOB SDL_IMAGE_DLLS ${SDL2_IMAGE_LIBRARY_DIR}/*.dll)
      
set(PRJ_SOURCES
    Maze.h

    Maze.cpp
    main.cpp
)

# add_compile_options(-Wall)
include_directories(${PROJECT_SOURCE_DIR}/../libgame ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${PRJ_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE libgame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
