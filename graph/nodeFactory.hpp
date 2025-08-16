#pragma once

#include <string>

#include "graph/node.hpp"

namespace graph {

class Graph;

class NodeFactory {
public:
    virtual ~NodeFactory() = default;

    virtual Node* createNode(Graph& graph, const std::string& handle) = 0;
    virtual Node* createNodeWithId(Graph& graph, NodeUniqueId nodeId, const std::string& handle) = 0;
};

}