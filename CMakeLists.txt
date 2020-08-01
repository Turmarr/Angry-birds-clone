cmake_minimum_required(VERSION 3.16.3)
set (CMAKE_CXX_STANDARD 11)
project(example)

include_directories("src")

set(EXECUTABLE_NAME example)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

file(GLOB SOURCES src/*.cpp src/*.png)
add_executable(${EXECUTABLE_NAME} ${SOURCES})
set(CMAKE_BUILD_TYPE Debug)

#if you have linux and can install box2d via sudo
#find_package(Box2D REQUIRED)
#target_link_libraries(${EXECUTABLE_NAME} Box2D)


#library as a .a file
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/libbox2d.a)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

#SFML library
find_package(SFML 2.5 REQUIRED network audio graphics window system)
target_link_libraries(${EXECUTABLE_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)