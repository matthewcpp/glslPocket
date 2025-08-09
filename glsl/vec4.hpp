#pragma once

#include "graphdev/node.hpp"
#include "graphdev/typeRegistry.hpp"

#include <array>

namespace graphdev::glsl
{

class Vec4 : public Node {
public:
    enum class OutputPortIndex {
        Value
    };

    enum class InputPortIndex {
        Value
    };

    using ValueType = std::array<float, 4>;

    Vec4(TypeRegistry& typeRegistry, const std::string& name);

    const ValueType& value() const { return _value; }
    void setValue(const ValueType& value) { _value = value; };
private:
    std::array<float, 4> _value;
};

}
