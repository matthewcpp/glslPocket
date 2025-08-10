#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

namespace glsl {

class Float : public graph::Node {
public:
    Float(graph::NodeUniqueId uniqueId, graph::TypeRegistry& typeRegistry, const std::string& name);

    float value() const { return _value; }
    void setValue(float value) {_value = value; }
private:
    float _value = 0.0f;
};

}