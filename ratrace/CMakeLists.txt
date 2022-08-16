project(ratrace)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11) 
    
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
file(GLOB SDL_DLLS ${SDL2_LIBRARY_DIR}/*.dll)
file(GLOB SDL_IMAGE_DLLS ${SDL2_IMAGE_LIBRARY_DIR}/*.dll)

set(ratrace_SRC
    Cheese.h
    EnemyMouse.h
    Mouse.h
    RatLevel.h
    ../tilemap/TileMap.h

    Cheese.cpp
    EnemyMouse.cpp
    Mouse.cpp
    RatLevel.cpp
    main.cpp
    ../tilemap/TileMap.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/../libgame
                    ${PROJECT_SOURCE_DIR}/../tilemap
                    ${SDL2_INCLUDE_DIRS}
                    ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(ratrace ${ratrace_SRC})

target_link_libraries(ratrace libgame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# post-build step
set(ASSET_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
add_custom_command(TARGET ratrace POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSET_OUTPUT_PATH})
add_custom_command(TARGET ratrace POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/font.png ${ASSET_OUTPUT_PATH})
add_custom_command(TARGET ratrace POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/ratrace.png ${ASSET_OUTPUT_PATH})
