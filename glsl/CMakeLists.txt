set(glsl_source_files
    builtin.hpp builtin.cpp
    compiler.hpp compiler.cpp
    flags.hpp
    float.hpp float.cpp
    module.hpp module.cpp
    nodeId.hpp
    operator.hpp operator.cpp
    swizzle.hpp swizzle.cpp
    vec.hpp vec.cpp
)

add_library(glsl STATIC ${glsl_source_files})
target_link_libraries(glsl PUBLIC graph)
set_target_properties(glsl PROPERTIES CXX_STANDARD 17)