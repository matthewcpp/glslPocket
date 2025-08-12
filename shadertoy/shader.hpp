#pragma once

#include "graph/nodeRegistry.hpp"
#include "graph/program.hpp"
#include "graph/typeRegistry.hpp"

namespace shadertoy {

class Shader {
public:
    Shader();

    void createNew();
    bool load(const std::string& path);
    bool write(const std::string& path);

    std::string compile();
private:
    graph::TypeRegistry _typeRegistry;
    graph::NodeRegistry _nodeRegistry;

public:
    graph::Program program;
    graph::UserFunction* mainImage;
};

}