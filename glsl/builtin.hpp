#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

namespace glsl {

class Builtin : public graph::Node {
public:
    enum class Function {
        Cos
    };
public:
    Builtin(graph::NodeUniqueId uniqueId, graph::TypeRegistry& typeRegistry, Function type, const std::string& name);

    Function function() const { return _function; }
    const std::string& functionName() const { return _functionName; }

private:
    Function _function;
    std::string _functionName;
};

}
