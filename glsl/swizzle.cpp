#include "glsl/swizzle.hpp"

#include "glsl/nodeId.hpp"
#include "graph/graph.hpp"

namespace glsl {

Swizzle::Swizzle(graph::NodeUniqueId uniqueId, graph::TypeRegistry& typeRegistry, const std::string& name)
    : Node(uniqueId, GlslNodeSwizzle, name), _typeRegistry(typeRegistry)
{
    // configure a default value for the swizzle
    _mask = "x";
    createInput("in", typeRegistry.getType("vec3"));
    createOutput("out", typeRegistry.getType("float"));
}

void Swizzle::setMask(const std::string& mask) {
    _mask = mask;

    auto& output = _outputs[0];

    switch (_mask.size()) {
        case 1:
            output.type = _typeRegistry.getType("float");
            break;
        
        case 2:
            output.type = _typeRegistry.getType("vec2");
            break;

        case 3:
            output.type = _typeRegistry.getType("vec3");
            break;

        case 4:
            output.type = _typeRegistry.getType("vec4");
            break;
    }
}

bool SwizzleEditor::setMask(const std::string& mask) {
    if (mask.size() > 4) {
        _errorString = "Swizzle mask can be at most 4 characters.";
        return false;
    }

    //TODO: check for existing connections in graph and update or remove them
    _swizzle->setMask(mask);

    return true;
}

}