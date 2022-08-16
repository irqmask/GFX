project(tilemap)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11) 
    
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(tilemap_SRC
    MyScene.h
    MyScene.cpp
    TileMap.h
    TileMap.cpp
    main.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/../libgame ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(tilemap ${tilemap_SRC})

target_link_libraries(tilemap libgame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# post-build step
set(ASSET_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSET_OUTPUT_PATH})
add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/font.png "${ASSET_OUTPUT_PATH}")
add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tiles_30x30_test.png "${ASSET_OUTPUT_PATH}")
