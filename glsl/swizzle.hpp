#pragma once

#include "graphdev/node.hpp"
#include "graphdev/typeRegistry.hpp"

namespace graphdev {
class Graph;
}

namespace graphdev::glsl {

class Swizzle : public Node {
public:
    Swizzle(TypeRegistry& typeRegistry, const std::string& name);

    const std::string& mask() const { return _mask; }

private:
    /** Note: this value does not perform any validation, use the SwizzleEditor */
    void setMask(const std::string& mask);

private:
    std::string _mask;
    TypeRegistry& _typeRegistry;

    friend class SwizzleEditor;
};

class SwizzleEditor {
public:
    SwizzleEditor(Swizzle* swizzle, graphdev::Graph& graph)
        : _swizzle(swizzle), _graph(graph) {}

    bool setMask(const std::string& mask);

    const std::string& errorStr() const { return _errorString; }

private:
    Swizzle* _swizzle;
    graphdev::Graph& _graph;
    std::string _errorString;
};

}
