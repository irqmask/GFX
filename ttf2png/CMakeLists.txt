project(ttf2png)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11) 
    
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB SDL_TTF_DLLS ${SDL2_TTF_LIBRARY_DIR}/*.dll)

set(ttf2png_SRC
    main.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/../libgame ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

add_executable(ttf2png ${ttf2png_SRC})

target_link_libraries(ttf2png libgame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# post-build step
if(WIN32)
    add_custom_command(TARGET ttf2png POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL_TTF_DLLS} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif(WIN32)
