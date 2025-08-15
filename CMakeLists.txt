cmake_minimum_required(VERSION 3.14)

project(graphdev CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(commands)
add_subdirectory(graph)
add_subdirectory(glsl)
add_subdirectory(shadertoy)

add_executable(buildshader main.cpp)
target_link_libraries(buildshader PRIVATE graph glsl shadertoy commands)
