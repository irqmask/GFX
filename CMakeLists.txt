project(GFX)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Evaluate build type
if (MSVC)
    set(PRJ_BUILDTYPE_SUBDIR
        $<$<CONFIG:Debug>:debug>$<$<CONFIG:RelWithDebInfo>:debug>$<$<CONFIG:Release>:release>$<$<CONFIG:MinSizeRel>:release>)

    set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
        $<$<CONFIG:Debug>:BUILD_DEBUG>
        $<$<CONFIG:RelWithDebInfo>:BUILD_DEBUG>
        $<$<CONFIG:Release>:BUILD_RELEASE>
        $<$<CONFIG:MinSizeRel>:BUILD_RELEASE>
    )
else ()
    if (NOT CMAKE_BUILD_TYPE)
        set (CMAKE_BUILD_TYPE Release CACHE STRING "Debug or Release build. Release is default." FORCE)
    endif ()

    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set (PRJ_BUILDTYPE_SUBDIR "release")
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set (PRJ_BUILDTYPE_SUBDIR "debug")
    else ()
        set (PRJ_BUILDTYPE_SUBDIR "unknown")
        message("Target build type unknown!")
    endif ()
endif ()

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PRJ_BUILDTYPE_SUBDIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PRJ_BUILDTYPE_SUBDIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PRJ_BUILDTYPE_SUBDIR})


add_subdirectory(libgame)

add_subdirectory(dirt)
add_subdirectory(joysticktest)
add_subdirectory(maze)
add_subdirectory(mazesolver)
add_subdirectory(ratrace)
add_subdirectory(sprites)
add_subdirectory(tetris)
add_subdirectory(tilemap)
add_subdirectory(ttf2png)
