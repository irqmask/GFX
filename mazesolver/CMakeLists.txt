project(mazesolver)

cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
file(GLOB SDL_DLLS ${SDL2_LIBRARY_DIR}/*.dll)
file(GLOB SDL_IMAGE_DLLS ${SDL2_IMAGE_LIBRARY_DIR}/*.dll)
      
set(PRJ_SOURCES
    MazeData.h
    MazeCreatorScene.h
    MazeSolverScene.h

    ../tilemap/TileMap.h

    MazeCreatorScene.cpp
    MazeSolverScene.cpp
    main.cpp

    ../tilemap/TileMap.cpp
)

# add_compile_options(-Wall)
include_directories(${PROJECT_SOURCE_DIR}/../libgame
                    ${PROJECT_SOURCE_DIR}/../tilemap
                    ${SDL2_INCLUDE_DIRS}
                    ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${PRJ_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE libgame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# post-build step
set(ASSET_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
# FIXME GLOBAL ASSET path
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/../assets/font.png "${ASSET_OUTPUT_PATH}")
