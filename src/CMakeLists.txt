cmake_minimum_required(VERSION 3.0)

project(balloon)

# The directory of CMake find_package modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

# Add linker flags if on UNIX
if(UNIX)
    set(linker_flags "-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer")
endif()

# Find required packages if on Windows
if(WIN32)
    # Set the SDL2 libraries path for find_package modules
    set(SDL2_PATH "${CMAKE_SOURCE_DIR}/lib")
    set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/lib")
    set(SDL2_MIXER_PATH "${CMAKE_SOURCE_DIR}/lib")
    set(SDL2_IMAGE_PATH "${CMAKE_SOURCE_DIR}/lib")

    find_package(SDL2 REQUIRED)
    find_package(SDL2_TTF REQUIRED)
    find_package(SDL2_MIXER REQUIRED)
    find_package(SDL2_IMAGE REQUIRED)

    # Include SDL header for program
    include_directories("${CMAKE_SOURCE_DIR}/lib/include")
endif()

# Include custom header for program
# include_directories("${CMAKE_SOURCE_DIR}/header")

if(UNIX)
    include_directories("/usr/include/SDL2")
endif()

add_executable(balloon globals.cpp init.cpp main.cpp sprites.cpp states.cpp texture.cpp classes.h globals.h texture.h)

target_link_libraries(balloon ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${linker_flags})

# Copy resources to binary folder
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
