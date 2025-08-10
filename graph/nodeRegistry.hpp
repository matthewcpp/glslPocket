#pragma once

#include "graph/node.hpp"

#include "graph/typeRegistry.hpp"

#include <functional>
#include <string>
#include <unordered_map>

namespace graphdev {

class NodeRegistry{
public:
    using CreateNodeFunc = std::function<Node*(TypeRegistry&)>;

    NodeRegistry(TypeRegistry& typeRegistry);

    bool registerNode(const std::string& nodeType, CreateNodeFunc nodeFunc);
    bool registerNodeWithType(const std::string& nodeType, const std::string typeName, CreateNodeFunc nodeFunc);

    Node* createNode(const std::string& nodeType);
    Node* createNodeForType(const std::string& typeName);

private:
    TypeRegistry& _typeRegistry;
    std::unordered_map<std::string, CreateNodeFunc> _nodeFuncs;
    std::unordered_map<std::string, CreateNodeFunc> _typeNodeFuncs;
};

}