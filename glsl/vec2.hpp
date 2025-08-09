#pragma once

#include "graphdev/node.hpp"
#include "graphdev/typeRegistry.hpp"

#include <array>

namespace graphdev::glsl
{

class Vec2 : public Node {
public:
    enum class OutputPortIndex {
        Value
    };

    enum class InputPortIndex {
        Value
    };

    Vec2(TypeRegistry& typeRegistry, const std::string& name);

    const std::array<float, 2> & value() const { return _value; }
private:
    std::array<float, 2> _value;
};

}
