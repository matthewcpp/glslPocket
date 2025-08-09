set(glsl_source_files
    flags.hpp
    nodeId.hpp
    builtin.hpp builtin.cpp
    float.hpp float.cpp
    operator.hpp operator.cpp
    vec2.hpp vec2.cpp
    vec3.hpp vec3.cpp
    vec4.hpp vec4.cpp
    swizzle.hpp swizzle.cpp
    module.hpp module.cpp
)

add_library(glsl STATIC ${glsl_source_files})
target_link_libraries(glsl PRIVATE graphdev)
set_target_properties(glsl PROPERTIES CXX_STANDARD 17)