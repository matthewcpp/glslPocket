#include "glsl/vec4.hpp"

#include "glsl/nodeId.hpp"

#include <algorithm>

namespace graphdev::glsl {

Vec4::Vec4(TypeRegistry& typeRegistry, const std::string& name)
    : Node(GlslNodeVec4, name)
{
    auto* vec4_type = typeRegistry.getType("vec4");
    createInput("in", vec4_type);
    createOutput("out", vec4_type);

    std::fill(_value.begin(), _value.end(), 0.0f);
}

}
