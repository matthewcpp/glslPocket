#include "glsl/float.hpp"

#include "glsl/nodeId.hpp"

namespace glsl {

Float::Float(graph::TypeRegistry& typeRegistry, const std::string& name)
    : Node(GlslNodeFloat, name)
    {
        auto* floatType = typeRegistry.getType("float");

        createInput("in", floatType);
        createOutput("out", floatType);
    }

}