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

    bool isValid() const {
        return !name.empty();
    }

    static const Property& invalid() {
        return _invalid;
    }

    std::string name;
    ValueType value;

private:
    static Property _invalid;
};

}
