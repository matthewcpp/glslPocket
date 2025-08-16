#pragma once

#include "glsl/nodeFactory.hpp"

namespace shadertoy {

class NodeFactory : public glsl::NodeFactory {
public:
    virtual graph::Node* createResolutionNode(graph::Graph& graph, graph::NodeUniqueId nodeId) override;

};

}