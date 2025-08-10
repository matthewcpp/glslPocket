#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

#include <array>

namespace graphdev::glsl {

class Vec : public Node {
public:
    enum class Type {
        Vec2, Vec3, Vec4
    };
    Vec(TypeRegistry& typeRegistry, Type vecType, const std::string& name);

    Type getVecType() const { return _vecType; }
    size_t getSize() const { return static_cast<size_t>(_vecType); }
    float getElement(size_t index) const { return _value[index]; }

private:
    Type _vecType;
    std::array<float, 4> _value;
};

}