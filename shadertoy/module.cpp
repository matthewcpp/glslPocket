#include "shadertoy/module.hpp"

#include "graphdev/typeRegistry.hpp"
#include "glsl/float.hpp"
#include "glsl/vec3.hpp"

namespace graphdev::shadertoy {

static Node* ShadertoyResolutionNode(TypeRegistry& typeRegistry) {
    auto* node = new glsl::Vec3(typeRegistry, "iResolution");
    node->flags |= graphdev::NodeFlagDefinedInScope;
    return node;
}

static Node* ShadertoyTimeNode(TypeRegistry& typeRegistry) {
    auto* node = new glsl::Vec3(typeRegistry, "iTime");
    node->flags |= graphdev::NodeFlagDefinedInScope;
    return node;
}

}

void shadertoy_module(graphdev::TypeRegistry& typeRegistry, graphdev::NodeRegistry& nodeRegistry)
{
    using namespace graphdev::shadertoy;
    nodeRegistry.registerNode("shadertoy::iResolution", ShadertoyResolutionNode);
    nodeRegistry.registerNode("shadertoy::iTime", ShadertoyTimeNode);
}