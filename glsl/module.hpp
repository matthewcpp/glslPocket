#pragma once

#include "graph/schemaRegistry.hpp"
#include "graph/typeRegistry.hpp"

namespace glsl {
    void initModule(graph::TypeRegistry& typeRegistry, graph::SchemaRegistry& schemaRegistry);
}

