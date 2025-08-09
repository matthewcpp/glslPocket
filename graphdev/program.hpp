#pragma once

#include "typeRegistry.hpp"
#include "nodeRegistry.hpp"
#include "userFunction.hpp"

#include <memory>
#include <unordered_map>

namespace graphdev {

class Program {
public:
    Program(TypeRegistry& typeRegistry, NodeRegistry& nodeRegistry) : _typeRegistry(typeRegistry), _nodeRegistry(nodeRegistry) {}

    UserFunction* createUserFunction(const std::string& name);
    UserFunction* getUserFunction(const std::string& name);

private:
    TypeRegistry& _typeRegistry;
    NodeRegistry& _nodeRegistry;
    std::unordered_map<std::string, std::unique_ptr<UserFunction>> _userFunctions;
};

}