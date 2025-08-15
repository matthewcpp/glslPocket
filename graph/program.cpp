#include "graph/program.hpp"

namespace graph {

UserFunction* Program::createUserFunction(const std::string& name) {
    if (_userFunctions.count(name)) {
        return nullptr;
    }

    auto userFunction = std::make_unique<UserFunction>(_typeRegistry, _schemaRegistry, hooks, name);
    auto* uf = userFunction.get();

    _userFunctions[name] = std::move(userFunction);

    return uf;
}

void Program::iterateUserFuncs(UserFunctionItrFunc func) const {
    for (const auto& userFunc : _userFunctions) {
        func(userFunc.second.get());
    }
}

UserFunction* Program::getUserFunction(const std::string& name) const {
    auto result = _userFunctions.find(name);

    return result != _userFunctions.end() ? result->second.get() : nullptr;
}

}