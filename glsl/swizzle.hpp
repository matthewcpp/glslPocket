#pragma once

#include "graph/node.hpp"
#include "graph/typeRegistry.hpp"

namespace graph {
class Graph;
}

namespace glsl {

class Swizzle : public graph::Node {
public:
    Swizzle(graph::TypeRegistry& typeRegistry, const std::string& name);

    const std::string& mask() const { return _mask; }

private:
    /** Note: this value does not perform any validation, use the SwizzleEditor */
    void setMask(const std::string& mask);

private:
    std::string _mask;
    graph::TypeRegistry& _typeRegistry;

    friend class SwizzleEditor;
};

class SwizzleEditor {
public:
    SwizzleEditor(Swizzle* swizzle, graph::Graph& graph)
        : _swizzle(swizzle), _graph(graph) {}

    bool setMask(const std::string& mask);

    const std::string& errorStr() const { return _errorString; }

private:
    Swizzle* _swizzle;
    graph::Graph& _graph;
    std::string _errorString;
};

}
