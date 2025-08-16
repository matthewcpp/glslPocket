#include "shadertoy/nodeFactory.hpp"

#include "graph/graph.hpp"
#include "graph/node.hpp"

namespace shadertoy {

graph::Node* NodeFactory::createResolutionNode(graph::Graph& graph, graph::NodeUniqueId nodeId) {
    graph::Node* node = nodeId != 0 ? graph.createNodeWithId(nodeId, "glsl::vec2", "iResolution") : graph.createNode("glsl::vec2", "iResolution");
    node->flags = graph::NodeFlags::NodeFlagDefinedInScope;

    return node;
}

}