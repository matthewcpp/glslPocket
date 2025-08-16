#pragma once

#include "graph/nodeFactory.hpp"

#include <functional>
#include <string>
#include <unordered_map>

namespace glsl {

class NodeFactory : public graph::NodeFactory {
public:
    virtual graph::Node* createResolutionNode(graph::Graph& graph, graph::NodeUniqueId nodeId) = 0;

    virtual graph::Node* createNode(graph::Graph& graph, const std::string& handle) override;
    virtual graph::Node* createNodeWithId(graph::Graph& graph, graph::NodeUniqueId nodeId, const std::string& handle) override;

public:
    NodeFactory();

    graph::NodeUniqueId lastCreatedId() const { return _lastCreatedNodeId; }

private:
    using FuncType = std::function<graph::Node*(graph::Graph&, graph::NodeUniqueId)>;
    std::unordered_map<std::string, FuncType> _funcMap;

    graph::NodeUniqueId _lastCreatedNodeId = 0;
};

}