#include "glsl/module.hpp"

#include "glsl/operator.hpp"
#include "glsl/builtin.hpp"
#include "glsl/swizzle.hpp"

#include "glsl/float.hpp"
#include "glsl/vec.hpp"

namespace graphdev::glsl {

static Node* GlslFloatNode(TypeRegistry& typeRegistry) {
    return new Float(typeRegistry, "float");
}

static Node* GlslVec2Node(TypeRegistry& typeRegistry) {
    return new Vec(typeRegistry, Vec::Type::Vec2, "vec2");
}

static Node* GlslVec3Node(TypeRegistry& typeRegistry) {
    return new Vec(typeRegistry, Vec::Type::Vec3, "vec3");
}

static Node* GlslVec4Node(TypeRegistry& typeRegistry) {
    return new Vec(typeRegistry, Vec::Type::Vec4, "vec4");
}

static Node* GlslAddNode(TypeRegistry& typeRegistry) {
    return new Operator(typeRegistry, Operator::Type::Add, "Add");
}

static Node* GlslSubtractNode(TypeRegistry& typeRegistry) {
    return new Operator(typeRegistry, Operator::Type::Subtract, "Subtract");
}

static Node* GlslMultiplyNode(TypeRegistry& typeRegistry) {
    return new Operator(typeRegistry, Operator::Type::Multiply, "Multiply");
}

static Node* GlslDivideNode(TypeRegistry& typeRegistry) {
    return new Operator(typeRegistry, Operator::Type::Divide, "Divide");
}

static Node* GlslCosNode(TypeRegistry& typeRegistry) {
    return new Builtin(typeRegistry, Builtin::Function::Cos, "cos");
}

static Node* GlslSwizzleNode(TypeRegistry& typeRegistry) {
    return new Swizzle(typeRegistry, "Swizzle");
}

}

void glslModuleInit(graphdev::TypeRegistry& typeRegistry, graphdev::NodeRegistry& nodeRegistry) {
    using namespace graphdev::glsl;
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