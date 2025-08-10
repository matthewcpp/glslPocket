#include "glsl/vec.hpp"
#include "glsl/nodeId.hpp"

namespace glsl {

Vec::Vec(graph::NodeUniqueId uniqueId, graph::TypeRegistry& typeRegistry, Type vecType, const std::string& name) 
    : Node(uniqueId, GlslNodeVec, name), _vecType(vecType)
{
    const graph::Type* outputType = nullptr;

    _properties.emplace_back("x", 0.0f);
    _properties.emplace_back("y", 0.0f);

    switch (getVecType()) {
        case Type::Vec2: 
            outputType = typeRegistry.getType("vec2");
            break;

        case Type::Vec3:
            outputType = typeRegistry.getType("vec3");
            _properties.emplace_back("z", 0.0f);
            break;

        case Type::Vec4:
            outputType = typeRegistry.getType("vec4");
            _properties.emplace_back("z", 0.0f);
            _properties.emplace_back("w", 0.0f);
            break;
    }

    createInput("in", outputType);
    createOutput("out", outputType);
}

}
