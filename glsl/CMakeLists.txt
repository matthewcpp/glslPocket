set(glsl_source_files
    compiler.hpp compiler.cpp
    flags.hpp
    module.hpp module.cpp
    nodeFactory.hpp nodeFactory.cpp
)

add_library(glsl STATIC ${glsl_source_files})
target_link_libraries(glsl PUBLIC graph)
set_target_properties(glsl PROPERTIES CXX_STANDARD 17)