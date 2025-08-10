#include "nodeRegistry.hpp"

#include "graph/enterNode.hpp"

namespace graphdev {

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

Node* NodeRegistry::createNode(const std::string& nodeType) {
    auto result = _nodeFuncs.find(nodeType);

    return result != _nodeFuncs.end() ? result->second(_typeRegistry) : nullptr;
}

Node* NodeRegistry::createNodeForType(const std::string& typeName) {
    auto result = _typeNodeFuncs.find(typeName);

    return result != _nodeFuncs.end() ? result->second(_typeRegistry) : nullptr;
}

}