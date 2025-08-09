#pragma once

#include "graphdev/nodeRegistry.hpp"
#include "graphdev/program.hpp"
#include "graphdev/typeRegistry.hpp"

namespace graphdev::shadertoy {

class Shader {
public:
    Shader();

private:
    TypeRegistry _typeRegistry;
    NodeRegistry _nodeRegistry;

public:
    graphdev::Program program;
    UserFunction* mainImage;
};

}