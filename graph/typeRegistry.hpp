#pragma once

#include "type.hpp"

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace graph {

class TypeRegistry {
public:
    TypeRegistry();
    Type* registerType(const std::string& name);
    const Type* getType(const std::string& name);

private:
    std::unordered_map<std::string, std::unique_ptr<Type>> _types;
    uint32_t _nextId = 0;
};

}