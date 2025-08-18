#include "glsl/module.hpp"

#include "graph/nodeId.hpp"
#include "graph/attribute.hpp"
#include "graph/function.hpp"
#include "graph/struct.hpp"
#include "graph/operator.hpp"
#include "graph/value.hpp"

namespace glsl {

static graph::Schema* vec2(const graph::Type* type) {
    graph::Schema* vec2 = new graph::Struct(type, "glsl::vec2");
    vec2->addProperty("x", 0.0f);
    vec2->addProperty("y", 0.0f);
    return vec2;
}

static graph::Schema* vec3(const graph::Type* type) {
    graph::Schema* vec3 = new graph::Struct(type, "glsl::vec3");
    vec3->addProperty("x", 0.0f);
    vec3->addProperty("y", 0.0f);
    vec3->addProperty("z", 0.0f);
    return vec3;
}

static graph::Schema* vec4(const graph::Type* type) {
    graph::Schema* vec4 = new graph::Struct(type, "glsl::vec4");
    vec4->addProperty("x", 0.0f);
    vec4->addProperty("y", 0.0f);
    vec4->addProperty("z", 0.0f);
    vec4->addProperty("w", 0.0f);
    return vec4;
}

void initModule(graph::TypeRegistry& typeRegistry, graph::SchemaRegistry& schemaRegistry) {
    using namespace glsl;
    const graph::Type* vec2Type = typeRegistry.registerType("vec2");
    const graph::Type* vec3Type = typeRegistry.registerType("vec3");
    const graph::Type* vec4Type = typeRegistry.registerType("vec4");

    schemaRegistry.addForType(vec2Type, vec2(vec2Type));
    schemaRegistry.addForType(vec3Type, vec3(vec3Type));
    schemaRegistry.addForType(vec4Type, vec4(vec4Type));

    // TODO: should these ben enabled by default in schema registry itself?
    schemaRegistry.add(new graph::Attribute());
    schemaRegistry.add(new graph::Operator());
    schemaRegistry.add(new graph::Value());
    schemaRegistry.add(new graph::Function());
}

}