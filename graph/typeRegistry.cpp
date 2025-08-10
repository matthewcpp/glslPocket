#include "typeRegistry.hpp"

namespace graph {

TypeRegistry::TypeRegistry(){
    registerType("any");
}

Type* TypeRegistry::registerType(const std::string& name) {
    auto type = std::make_unique<Type>(_nextId++, name);
    Type* t = type.get();

    _types[name] = std::move(type);

    return t;
}

const Type* TypeRegistry::getType(const std::string& name) {
    auto result = _types.find(name);

    return result != _types.end() ? result->second.get() : nullptr;
}

}