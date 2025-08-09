#include "glsl/vec3.hpp"

#include "glsl/nodeId.hpp"

#include <algorithm>

namespace graphdev::glsl {

Vec3::Vec3(TypeRegistry& typeRegistry, const std::string& name)
    : Node(GlslNodeVec3, name)
{
    auto* vec3Type = typeRegistry.getType("vec3");

    createInput("in", vec3Type);
    createOutput("out", vec3Type);

    std::fill(_value.begin(), _value.end(), 0.0f);
}

}
