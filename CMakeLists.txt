cmake_minimum_required(VERSION 3.14)

project(graphdev CXX)

add_subdirectory(graphdev)
add_subdirectory(glsl)
add_subdirectory(shadertoy)

add_executable(buildshader main.cpp)
target_link_libraries(buildshader PRIVATE graphdev glsl shadertoy)
