#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

#include <array>

namespace glsl {

class Vec : public graph::Node {
public:
    enum class Type {
        Vec2 = 2, Vec3 = 3, Vec4 = 4
    };
    Vec(graph::NodeUniqueId uniqueId, graph::TypeRegistry& typeRegistry, Type vecType, const std::string& name);

    Type getVecType() const { return _vecType; }
    size_t getSize() const { return static_cast<size_t>(_vecType); }

private:
    Type _vecType;
};

}