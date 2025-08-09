#pragma once

#include "graphdev/node.hpp"
#include "graphdev/typeRegistry.hpp"

#include <array>

namespace graphdev::glsl
{

class Vec3 : public Node {
public:
    enum class OutputPortIndex {
        Value
    };

    enum class InputPortIndex {
        Value
    };

    Vec3(TypeRegistry& typeRegistry, const std::string& name);

    const std::array<float, 3> & value() const { return _value; }
private:
    std::array<float, 3> _value;
};

}
