#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

namespace graphdev::glsl {

class Operator : public Node {
public:
    enum class OutputPortIndex {
        Out
    };

    enum class InputPortIndex {
        A, B
    };

    enum class Type {
        Add, Subtract, Multiply, Divide
    };
public:
    Operator(TypeRegistry& typeRegistry, Type type, const std::string& name);

    Type type() const { return _type; }
    void setType(Type type) {_type = type; }

private:
    Type _type;
};

}
