#include "graph/connection.hpp"

#include "graph/node.hpp"

namespace graph {

std::string Connection::toString() const {
    const auto& fromPort = fromNode->outputs()[fromPortIndex];
    const auto& toPort = toNode->inputs()[toPortIndex];

    std::string str;
    str.append("Connection (").append(std::to_string(_uniqueId)).append("): ");
    str.append(fromNode->name()).append(".").append(fromPort.name).append(" (").append(std::to_string(fromNode->uniqueId())).append(")");
    str.append(" ---> ");
    str.append(toNode->name()).append(".").append(toPort.name).append(" (").append(std::to_string(toNode->uniqueId())).append(")");
    
    return str;
}

}