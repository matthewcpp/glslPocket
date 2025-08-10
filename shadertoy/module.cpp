#include "shadertoy/module.hpp"

#include "graph/typeRegistry.hpp"
#include "glsl/float.hpp"
#include "glsl/vec.hpp"

namespace shadertoy {

static graph::Node* ShadertoyResolutionNode(graph::TypeRegistry& typeRegistry) {
    auto* node = new glsl::Vec(typeRegistry, glsl::Vec::Type::Vec3, "iResolution");
    node->flags |= graph::NodeFlagDefinedInScope;
    return node;
}

static graph::Node* ShadertoyTimeNode(graph::TypeRegistry& typeRegistry) {
    auto* node = new glsl::Float(typeRegistry, "iTime");
    node->flags |= graph::NodeFlagDefinedInScope;
    return node;
}

}

void shadertoyModuleInit(graph::TypeRegistry& typeRegistry, graph::NodeRegistry& nodeRegistry)
{
    using namespace shadertoy;
    nodeRegistry.registerNode("shadertoy::iResolution", ShadertoyResolutionNode);
    nodeRegistry.registerNode("shadertoy::iTime", ShadertoyTimeNode);
}