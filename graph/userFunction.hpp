#pragma once

#include "graph/graph.hpp"
#include "graph/typeRegistry.hpp"
#include "graph/schemaRegistry.hpp"

#include <string>
#include <vector>

namespace graph {

class UserFunction {
public:
    UserFunction(TypeRegistry& typeRegistry, SchemaRegistry& schemaRegistry, Hooks& hooks, const std::string& name)
        :graph(schemaRegistry, hooks), _typeRegistry(typeRegistry), name(name) {}

    struct Parameter{
        Parameter(const std::string& name, const Type* type, uint32_t flags) : name(name), type(type), flags(flags) {}
    
        std::string name;
        const Type* type;
        uint32_t flags;
    };

    /** Used only when creating a new function.
     * Will create parameter and return nodes.
     */
    bool initializeGraph();
    bool createParameter(const std::string& name, const std::string& typeName, uint32_t flags);

    std::string name;
    Type* returnType = nullptr;
    Node* exitNode = nullptr;
    std::vector<Parameter> parameters;
    Graph graph;
    TypeRegistry& _typeRegistry;
};

}