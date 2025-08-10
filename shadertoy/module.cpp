#include "shadertoy/module.hpp"

#include "graphdev/typeRegistry.hpp"
#include "glsl/float.hpp"
#include "glsl/vec.hpp"

namespace graphdev::shadertoy {

static Node* ShadertoyResolutionNode(TypeRegistry& typeRegistry) {
    auto* node = new glsl::Vec(typeRegistry, glsl::Vec::Type::Vec3, "iResolution");
    node->flags |= graphdev::NodeFlagDefinedInScope;
    return node;
}

static Node* ShadertoyTimeNode(TypeRegistry& typeRegistry) {
    auto* node = new glsl::Float(typeRegistry, "iTime");
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