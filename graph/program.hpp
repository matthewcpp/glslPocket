#pragma once

#include "graph/hooks.hpp"
#include "graph/schemaRegistry.hpp"
#include "graph/typeRegistry.hpp"
#include "graph/userFunction.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

namespace graph {

class Program {
public:
    Program(TypeRegistry& typeRegistry, SchemaRegistry& schemaRegistry) : _typeRegistry(typeRegistry), _schemaRegistry(schemaRegistry) {}

    UserFunction* createUserFunction(const std::string& name);
    UserFunction* getUserFunction(const std::string& name) const;

    using UserFunctionItrFunc = std::function<void(const UserFunction*)>;
    void iterateUserFuncs(UserFunctionItrFunc func) const;

    Hooks hooks;
private:
    TypeRegistry& _typeRegistry;
    SchemaRegistry& _schemaRegistry;
    std::unordered_map<std::string, std::unique_ptr<UserFunction>> _userFunctions;
};

}