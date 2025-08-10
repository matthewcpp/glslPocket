#include "glsl/module.hpp"

#include "glsl/operator.hpp"
#include "glsl/builtin.hpp"
#include "glsl/swizzle.hpp"

#include "glsl/float.hpp"
#include "glsl/vec.hpp"

namespace glsl {

static graph::Node* GlslFloatNode(graph::TypeRegistry& typeRegistry) {
    return new Float(typeRegistry, "float");
}

static graph::Node* GlslVec2Node(graph::TypeRegistry& typeRegistry) {
    return new Vec(typeRegistry, Vec::Type::Vec2, "vec2");
}

static graph::Node* GlslVec3Node(graph::TypeRegistry& typeRegistry) {
    return new Vec(typeRegistry, Vec::Type::Vec3, "vec3");
}

static graph::Node* GlslVec4Node(graph::TypeRegistry& typeRegistry) {
    return new Vec(typeRegistry, Vec::Type::Vec4, "vec4");
}

static graph::Node* GlslAddNode(graph::TypeRegistry& typeRegistry) {
    return new Operator(typeRegistry, Operator::Type::Add, "Add");
}

static graph::Node* GlslSubtractNode(graph::TypeRegistry& typeRegistry) {
    return new Operator(typeRegistry, Operator::Type::Subtract, "Subtract");
}

static graph::Node* GlslMultiplyNode(graph::TypeRegistry& typeRegistry) {
    return new Operator(typeRegistry, Operator::Type::Multiply, "Multiply");
}

static graph::Node* GlslDivideNode(graph::TypeRegistry& typeRegistry) {
    return new Operator(typeRegistry, Operator::Type::Divide, "Divide");
}

static graph::Node* GlslCosNode(graph::TypeRegistry& typeRegistry) {
    return new Builtin(typeRegistry, Builtin::Function::Cos, "cos");
}

static graph::Node* GlslSwizzleNode(graph::TypeRegistry& typeRegistry) {
    return new Swizzle(typeRegistry, "Swizzle");
}

}

void glslModuleInit(graph::TypeRegistry& typeRegistry, graph::NodeRegistry& nodeRegistry) {
    using namespace glsl;
    nodeRegistry.registerNode("glsl::swizzle", GlslSwizzleNode);
    nodeRegistry.registerNode("glsl::add", GlslAddNode);
    nodeRegistry.registerNode("glsl::multiply", GlslMultiplyNode);
    nodeRegistry.registerNode("glsl::divide", GlslDivideNode);

    nodeRegistry.registerNode("glsl::cos", GlslCosNode);

    nodeRegistry.registerNodeWithType("glsl::float", typeRegistry.registerType("float")->name(), GlslFloatNode);
    nodeRegistry.registerNodeWithType("glsl::vec2", typeRegistry.registerType("vec2")->name(), GlslVec2Node);
    nodeRegistry.registerNodeWithType("glsl::vec3", typeRegistry.registerType("vec3")->name(), GlslVec3Node);
    nodeRegistry.registerNodeWithType("glsl::vec4", typeRegistry.registerType("vec4")->name(), GlslVec4Node);
}