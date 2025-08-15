#include "graph/schemaRegistry.hpp"

namespace graph {

bool SchemaRegistry::add(Schema* schema) {
    auto result = _schemas.emplace(schema->name(), std::unique_ptr<Schema>());
    if (result.second) {
        result.first->second.reset(schema);
        return true;
    }

    return false;
}

bool SchemaRegistry::addForType(const Type* type, Schema* schema) {
    if (_typeSchemas.count(type) == 0 && add(schema)) {
        _typeSchemas[type] = schema;
        return true;
    }

    return false;
}

const Schema* SchemaRegistry::get(const std::string& name) {
    auto result = _schemas.find(name);

    return result != _schemas.end() ? result->second.get() : nullptr;
}

const Schema* SchemaRegistry::getForType(const Type* type) {
    auto result = _typeSchemas.find(type);

    return result != _typeSchemas.end() ? result->second : nullptr;
}

}