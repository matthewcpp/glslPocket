#pragma once

#include "graphdev/node.hpp"
#include "graphdev/typeRegistry.hpp"

namespace graphdev::glsl {

class Builtin : public Node {
public:
    enum class Function {
        Cos
    };
public:
    Builtin(TypeRegistry& typeRegistry, Function type, const std::string& name);

    Function function() const { return _function; }
    const std::string& functionName() const { return _functionName; }

private:
    Function _function;
    std::string _functionName;
};

}
