set(shadertoy_source_files
    module.hpp module.cpp
    nodeFactory.hpp nodeFactory.cpp
    shader.hpp shader.cpp
)

add_library(shadertoy STATIC ${shadertoy_source_files})
target_link_libraries(shadertoy PUBLIC glsl)
set_target_properties(shadertoy PROPERTIES CXX_STANDARD 17)
