cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 11)
project(Angry_Birds)

#include_directories(src/Box2D/box2d/)

set(EXECUTABLE_NAME test)

file(GLOB SOURCES src/*.cpp src/*.hpp src/Box2D/*)
add_executable(${EXECUTABLE_NAME} ${SOURCES})
set(CMAKE_BUILD_TYPE Debug)

#find_package(Box2D REQUIRED)
#target_link_libraries(${EXECUTABLE_NAME} Box2D)

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.4 REQUIRED network audio graphics window system)

target_link_libraries(${EXECUTABLE_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)