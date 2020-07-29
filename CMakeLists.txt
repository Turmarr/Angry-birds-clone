cmake_minimum_required(VERSION 3.16.3)
project(testlevel)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp" "src/*.hpp")
 
add_executable(testlevel ${SOURCES})