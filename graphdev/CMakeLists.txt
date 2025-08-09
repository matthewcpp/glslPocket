set(graphdev_source_files
    connection.hpp
    enterNode.hpp enterNode.cpp
    graph.hpp graph.cpp
    node.hpp
    nodeRegistry.hpp nodeRegistry.cpp
    program.hpp program.cpp
    typeRegistry.hpp typeRegistry.cpp
    userFunction.hpp userFunction.cpp
    type.hpp
)

add_library(graphdev STATIC ${graphdev_source_files})
target_include_directories(graphdev PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
set_target_properties(graphdev PROPERTIES CXX_STANDARD 17)