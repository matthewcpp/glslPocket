#include "nodeRegistry.hpp"

#include "graph/enterNode.hpp"

namespace graph {

NodeRegistry::NodeRegistry(TypeRegistry& typeRegistry) 
    : _typeRegistry(typeRegistry) 
{
    registerNode("graphdev::enter", enterNode);
}

bool NodeRegistry::registerNode(const std::string& nodeType, CreateNodeFunc nodeFunc) {
    if (_nodeFuncs.count(nodeType)) {
        return false;
    }

    _nodeFuncs[nodeType] = nodeFunc;

    return true;
}

bool NodeRegistry::registerNodeWithType(const std::string& nodeType, const std::string typeName, CreateNodeFunc nodeFunc) {
    if (_typeNodeFuncs.count(typeName)) {
        return false;
    }

    if (!registerNode(nodeType, nodeFunc)) {
        return false;
    }

    _typeNodeFuncs[typeName] = nodeFunc;

    return true;
}

Node* NodeRegistry::createNode(NodeUniqueId uniqueId, const std::string& nodeType) {
    auto result = _nodeFuncs.find(nodeType);

    return result != _nodeFuncs.end() ? result->second(uniqueId, _typeRegistry) : nullptr;
}

Node* NodeRegistry::createNodeForType(NodeUniqueId uniqueId, const std::string& typeName) {
    auto result = _typeNodeFuncs.find(typeName);

    return result != _nodeFuncs.end() ? result->second(uniqueId, _typeRegistry) : nullptr;
}

}