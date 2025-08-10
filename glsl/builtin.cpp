#include "glsl/builtin.hpp"

#include "glsl/nodeId.hpp"

namespace glsl {

Builtin::Builtin(graph::NodeUniqueId uniqueId, graph::TypeRegistry& typeRegistry, Function type, const std::string& name)
    :Node(uniqueId, GlslNodeBuiltin, name), _function(type)
{
    // Todo: handle multiple function signatures in switch below
    auto* vec3Type = typeRegistry.getType("vec3");
    createInput("in", vec3Type);
    createOutput("out", vec3Type);

    switch(_function) {
        case Builtin::Function::Cos:
            _functionName = "cos";
            break;
    }
}

}
