#include "glsl/nodeFactory.hpp"

#include "graph/graph.hpp"
#include "graph/node.hpp"
#include "graph/attribute.hpp"
#include "graph/function.hpp"
#include "graph/operator.hpp"
#include "graph/value.hpp"

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

static inline graph::Node* _createResolutionNode(graph::Graph& graph, graph::NodeUniqueId nodeId) {
    graph::Node* node = nodeId != 0 ? graph.createNodeWithId(nodeId, "glsl::vec2", "glsl::resolution") : graph.createNode("glsl::vec2", "glsl::resolution");
    node->flags = graph::NodeFlags::NodeFlagDefinedInScope | graph::NodeFlags::PlatformDependant;

    return node;
}

static inline graph::Node* _createTimeNode(graph::Graph& graph, graph::NodeUniqueId nodeId) {
    graph::Node* node = nodeId != 0 ? graph.createNodeWithId(nodeId, "graph::value", "glsl::time") : graph.createNode("graph::value", "glsl::time");
    node->flags = graph::NodeFlags::NodeFlagDefinedInScope | graph::NodeFlags::PlatformDependant;

    return node;
}

static inline graph::Node* _createAttributeNode(graph::Graph& graph, graph::NodeUniqueId nodeId) {
    graph::Node* node = nodeId != 0 ? graph.createNodeWithId(nodeId, "graph::attribute", "swizzle") : graph.createNode("graph::attribute", "swizzle");
    graph::AttributeNode attribute(node);
    attribute.setAttribute("x");

    return node;
}

static inline graph::Node* _createOperatorNode(graph::Graph& graph, graph::NodeUniqueId nodeId, const std::string& opName, const std::string& op) {
    graph::Node* node = nodeId != 0 ? graph.createNodeWithId(nodeId, "graph::operator", opName) : graph.createNode("graph::operator", opName);
    graph::OperatorNode operatorNode(node);
    operatorNode.setOperator(op);

    return node;
}

static inline graph::Node* _createValueNode(graph::Graph& graph, graph::NodeUniqueId nodeId, const std::string& valueName, const graph::Property::ValueType& value) {
    graph::Node* node = nodeId != 0 ? graph.createNodeWithId(nodeId, "graph::value", valueName) : graph.createNode("graph::value", valueName);
    graph::ValueNode valueNode(node);
    valueNode.setValue(value);

    return node;
}

static inline graph::Node* _createFunctionNode(graph::Graph& graph, graph::NodeUniqueId nodeId, const std::string functionName) {
    graph::Node* node = nodeId != 0 ? graph.createNodeWithId(nodeId, "graph::function", functionName) : graph.createNode("graph::function", functionName);
    graph::FunctionNode functionNode(node);
    functionNode.setFunctionName(functionName);

    node->createInput("in", nullptr);
    node->createOutput("out", nullptr);

    return node;
}

NodeFactory::NodeFactory() {
    _funcMap["resolution"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createResolutionNode(graph, nodeId); };
    _funcMap["time"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createTimeNode(graph, nodeId); };

    _funcMap["vec2"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createStructNode(graph, nodeId, "glsl::vec2", "vec2"); };
    _funcMap["vec3"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createStructNode(graph, nodeId, "glsl::vec3", "vec3"); };
    _funcMap["vec4"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createStructNode(graph, nodeId, "glsl::vec4", "vec4"); };
    _funcMap["swizzle"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createAttributeNode(graph, nodeId); };
    _funcMap["add"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createOperatorNode(graph, nodeId, "add", "+"); };
    _funcMap["subtract"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createOperatorNode(graph, nodeId, "subtract", "-"); };
    _funcMap["multiply"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createOperatorNode(graph, nodeId, "multiply", "*"); };
    _funcMap["divide"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createOperatorNode(graph, nodeId, "divide", "/"); };

    _funcMap["float"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createValueNode(graph, nodeId, "float", 0.0f); };

    _funcMap["cos"] = [this](graph::Graph& graph, graph::NodeUniqueId nodeId){ return _createFunctionNode(graph, nodeId, "cos"); };
}

}