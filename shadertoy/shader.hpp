#pragma once

#include "graph/nodeRegistry.hpp"
#include "graph/program.hpp"
#include "graph/typeRegistry.hpp"

namespace shadertoy {

class Shader {
public:
    Shader();

    std::string compile();
private:
    graph::TypeRegistry _typeRegistry;
    graph::NodeRegistry _nodeRegistry;

public:
    graph::Program program;
    graph::UserFunction* mainImage;
};

}