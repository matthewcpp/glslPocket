set(shadertoy_source_files
    compiler.hpp compiler.cpp
    module.hpp module.cpp
    shader.hpp shader.cpp
)

add_library(shadertoy STATIC ${shadertoy_source_files})
target_link_libraries(shadertoy PUBLIC graphdev glsl)
set_target_properties(shadertoy PROPERTIES CXX_STANDARD 17)
