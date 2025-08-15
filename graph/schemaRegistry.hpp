#pragma once

#include "graph/schema.hpp"
#include "graph/type.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace graph {

class SchemaRegistry {
public:
    /** Note: the registry will manage the lifetime of the pointer passed into this function */
    bool add(Schema* schema);

    /** Note: the registry will manage the lifetime of the pointer passed into this function */
    bool addForType(const Type* type, Schema* schema);

    const Schema* get(const std::string& name);
    const Schema* getForType(const Type* type);

private:
    std::unordered_map<std::string, std::unique_ptr<Schema>> _schemas;
    std::unordered_map<const Type*, const Schema*> _typeSchemas;
};

}