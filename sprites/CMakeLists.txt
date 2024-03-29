project(sprites)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11) 

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB SDL_DLLS "${SDL2_LIBRARY_DIR}/*.dll")
file(GLOB SDL_IMAGE_DLLS "${SDL2_IMAGE_LIBRARY_DIR}/*.dll")

#if you don't want the full compiler output, remove the following line
set(CMAKE_VERBOSE_MAKEFILE ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/${BUILD_DIR_POSTFIX} CACHE STRING "Do not change this setting." FORCE)
        
set(sprites_SRC
    SpriteDemo.h
    SpriteDemo.cpp
    main.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/../libgame ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(sprites ${sprites_SRC})

target_link_libraries(sprites libgame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# post-build step
set(ASSET_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
add_custom_command(TARGET sprites POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSET_OUTPUT_PATH})
add_custom_command(TARGET sprites POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/spritexb-4248.png ${ASSET_OUTPUT_PATH})
