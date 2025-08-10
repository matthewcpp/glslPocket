#include "glsl/vec.hpp"
#include "glsl/nodeId.hpp"

namespace graphdev::glsl {

Vec::Vec(TypeRegistry& typeRegistry, Type vecType, const std::string& name) 
    : Node(GlslNodeVec, name), _vecType(vecType)
{
    auto* vec2Type = [this, &typeRegistry]() -> const graphdev::Type* {
        switch (getVecType()) {
            case Type::Vec2:
                return typeRegistry.getType("vec2");
            case Type::Vec3:
                return typeRegistry.getType("vec3");
            case Type::Vec4:
                return typeRegistry.getType("vec4");
            default:
                return nullptr;
        }
    }();

    createInput("in", vec2Type);
    createOutput("out", vec2Type);

    std::fill(_value.begin(), _value.end(), 0.0f);
}

}
