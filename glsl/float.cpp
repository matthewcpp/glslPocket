#include "glsl/float.hpp"

#include "glsl/nodeId.hpp"

namespace glsl {

Float::Float(graph::NodeUniqueId uniqueId, graph::TypeRegistry& typeRegistry, const std::string& name)
    : Node(uniqueId, GlslNodeFloat, name)
    {
        auto* floatType = typeRegistry.getType("float");

        createInput("in", floatType);
        createOutput("out", floatType);
    }

}