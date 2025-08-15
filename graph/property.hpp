#pragma once

#include <string>
#include <variant>

namespace graph {

struct Property {
    using ValueType = std::variant<float, std::string>;

    enum class TypeIndex {
        Float, String
    };

    Property() = default;
    Property(const std::string& name, const ValueType& value)
        : name(name), value(value) {};

    bool operator==(const Property& other) const {
        return name == other.name && value == other.value;
    }

    bool operator!=(const Property& other) const {
        return !(*this == other);
    }

    std::string name;
    ValueType value;
};

}
