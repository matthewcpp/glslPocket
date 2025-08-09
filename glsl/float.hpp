#pragma once

#include "graphdev/node.hpp"
#include "graphdev/typeRegistry.hpp"

namespace graphdev::glsl {

class Float : public Node {
public:
    Float(TypeRegistry& typeRegistry, const std::string& name);

    float value() const { return _value; }
    void setValue(float value) {_value = value; }
private:
    float _value = 0.0f;
};

}