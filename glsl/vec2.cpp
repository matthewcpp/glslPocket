#include "glsl/vec2.hpp"

#include "glsl/nodeId.hpp"

#include <algorithm>

namespace graphdev::glsl {

Vec2::Vec2(TypeRegistry& typeRegistry, const std::string& name)
    : Node(GlslNodeVec2, name)
{
    auto* vec2Type = typeRegistry.getType("vec2");

    createInput("in", vec2Type);
    createOutput("out", vec2Type);

    std::fill(_value.begin(), _value.end(), 0.0f);
}

}
