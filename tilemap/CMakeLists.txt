project(tilemap)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11) 
    
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
file(GLOB SDL_DLLS ${SDL2_LIBRARY_DIR}/*.dll)
file(GLOB SDL_IMAGE_DLLS ${SDL2_IMAGE_LIBRARY_DIR}/*.dll)

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
add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/font.png ${EXECUTABLE_OUTPUT_PATH}/Debug)
add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/font.png ${EXECUTABLE_OUTPUT_PATH}/Release)
add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tiles_30x30_test.png ${EXECUTABLE_OUTPUT_PATH}/Debug)
add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/tiles_30x30_test.png ${EXECUTABLE_OUTPUT_PATH}/Release)

if(WIN32)
    add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL_DLLS} ${EXECUTABLE_OUTPUT_PATH}/Debug)
    add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL_DLLS} ${EXECUTABLE_OUTPUT_PATH}/Release)
    add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL_IMAGE_DLLS} ${EXECUTABLE_OUTPUT_PATH}/Debug)
    add_custom_command(TARGET tilemap POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL_IMAGE_DLLS} ${EXECUTABLE_OUTPUT_PATH}/Release)
endif(WIN32)
