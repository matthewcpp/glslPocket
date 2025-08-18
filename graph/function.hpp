#pragma once

#include "graph/node.hpp"
#include "graph/schema.hpp"
#include "graph/nodeId.hpp"

namespace graph {

class Function : public Schema {
public:
    Function() : Schema("graph::function", GraphdevNodeFunction) {
        addProperty("function::name", std::string());
    }

};

class FunctionNode {
public:
    FunctionNode(Node* node) : _node(node) {}

    bool isValid() const { return _node->typeId() == GraphdevNodeFunction; }

    std::string getFunctionName() const {
        const auto& property = _node->getProperty("function::name");

        return std::get<std::string>(property.value);
    }

    void setFunctionName(const std::string& name) {
        _node->setProperty("function::name", name);
    }

private:
    Node* _node;
};

}