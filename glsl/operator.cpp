#include "glsl/operator.hpp"

#include "glsl/nodeId.hpp"

namespace glsl {

Operator::Operator(graph::TypeRegistry& typeRegistry, Type type, const std::string& name)
    :Node(GlslNodeOperator, name), _type(type)
{
    auto* vec3Type = typeRegistry.getType("vec3");
    createInput("a", vec3Type);
    createInput("b", vec3Type);
    createOutput("out", vec3Type);
}

}
