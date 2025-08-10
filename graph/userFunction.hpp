#pragma once

#include "graph.hpp"

#include <string>
#include <vector>

namespace graph {

class UserFunction {
public:
    UserFunction(TypeRegistry& typeRegistry, NodeRegistry& nodeRegistry, const std::string& name)
        :graph(nodeRegistry), _typeRegistry(typeRegistry), name(name) {}

    struct Parameter{
        Parameter(const std::string& name, const Type* type, uint32_t flags) : name(name), type(type), flags(flags) {}
    
        std::string name;
        const Type* type;
        uint32_t flags;
    };

    bool initializeGraph();
    bool createParameter(const std::string& name, const std::string& typeName, uint32_t flags);

    std::string name;
    Type* returnType = nullptr;
    Node* enterNode = nullptr;
    std::vector<Parameter> parameters;
    Graph graph;
    TypeRegistry& _typeRegistry;
};

}