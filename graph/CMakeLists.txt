set(graphdev_source_files
    connection.hpp
    exitNode.hpp exitNode.cpp
    graph.hpp graph.cpp
    node.hpp
    nodeRegistry.hpp nodeRegistry.cpp
    program.hpp program.cpp
    typeRegistry.hpp typeRegistry.cpp
    userFunction.hpp userFunction.cpp
    type.hpp

    jsonReader.hpp jsonReader.cpp
)

add_library(graph STATIC ${graphdev_source_files})
target_include_directories(graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
set_target_properties(graph PROPERTIES CXX_STANDARD 17)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(graph PRIVATE nlohmann_json::nlohmann_json)