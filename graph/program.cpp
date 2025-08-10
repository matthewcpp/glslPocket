#include "graph/program.hpp"

namespace graphdev {

UserFunction* Program::createUserFunction(const std::string& name) {
    if (_userFunctions.count(name)) {
        return nullptr;
    }

    auto userFunction = std::make_unique<UserFunction>(_typeRegistry, _nodeRegistry, name);
    auto* uf = userFunction.get();

    _userFunctions[name] = std::move(userFunction);

    return uf;
}

UserFunction* Program::getUserFunction(const std::string& name) const {
    auto result = _userFunctions.find(name);

    return result != _userFunctions.end() ? result->second.get() : nullptr;
}

}