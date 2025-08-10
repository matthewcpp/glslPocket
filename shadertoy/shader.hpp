#pragma once

#include "graph/nodeRegistry.hpp"
#include "graph/program.hpp"
#include "graph/typeRegistry.hpp"

namespace graphdev::shadertoy {

class Shader {
public:
    Shader();

    std::string compile();
private:
    TypeRegistry _typeRegistry;
    NodeRegistry _nodeRegistry;

public:
    graphdev::Program program;
    UserFunction* mainImage;
};

}