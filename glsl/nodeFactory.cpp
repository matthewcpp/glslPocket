#include "glsl/nodeFactory.hpp"

#include "graph/graph.hpp"
#include "graph/node.hpp"

namespace glsl {

graph::Node* NodeFactory::createNode(graph::Graph& graph, const std::string& handle) {
    return createNodeWithId(graph, 0, handle);
}

graph::Node* NodeFactory::createNodeWithId(graph::Graph& graph, graph::NodeUniqueId nodeId, const std::string& handle) {
    auto func = _funcMap.find(handle);

    if (func == _funcMap.end()) {
        return nullptr;
    }

    graph::Node* node = func->second(graph, nodeId);
    _lastCreatedNodeId = node ? node->uniqueId() : 0;

    return node;
}


static inline graph::Node* _createStructNode(graph::Graph& graph, graph::NodeUniqueId nodeId, const std::string& schema, const std::string& name) {
    return nodeId != 0 ? graph.createNodeWithId(nodeId, schema, name): graph.createNode(schema, name);
}

NodeFactory::NodeFactory() {
    _funcMap["vec2"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createStructNode(graph, nodeId, "glsl::vec2", "vec2"); };
    _funcMap["vec3"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createStructNode(graph, nodeId, "glsl::vec2", "vec2"); };
    _funcMap["vec4"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createStructNode(graph, nodeId, "glsl::vec2", "vec2"); };
    _funcMap["resolution"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return createResolutionNode(graph, nodeId); };
}

}