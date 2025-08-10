#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

namespace glsl {

class Float : public graph::Node {
public:
    Float(graph::NodeUniqueId uniqueId, graph::TypeRegistry& typeRegistry, const std::string& name);
};

}