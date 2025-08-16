set (commands_sources
    commandProcessor.hpp commandProcessor.cpp

    command.hpp
    createConnection.hpp createConnection.cpp
    createNode.hpp createNode.cpp
    setProperty.hpp setProperty.cpp

    nodeConnections.hpp nodeConnections.cpp
)

add_library(commands STATIC ${commands_sources})
target_link_libraries(commands PRIVATE graph)