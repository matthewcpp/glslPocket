set(graphdev_source_files
    connection.hpp
    graph.hpp graph.cpp
    node.hpp
    program.hpp program.cpp
    property.hpp property.cpp
    
    schemaRegistry.hpp schemaRegistry.cpp
    typeRegistry.hpp typeRegistry.cpp
    userFunction.hpp userFunction.cpp
    type.hpp

    schema.hpp schema.cpp
    attribute.hpp
    function.hpp
    operator.hpp
    struct.hpp
    value.hpp

    jsonReader.hpp jsonReader.cpp
    jsonWriter.hpp jsonWriter.cpp
)

add_library(graph STATIC ${graphdev_source_files})
target_include_directories(graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
set_target_properties(graph PROPERTIES CXX_STANDARD 17)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(graph PRIVATE nlohmann_json::nlohmann_json)