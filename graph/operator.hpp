#pragma once

#include "graph/schema.hpp"
#include "graph/node.hpp"
#include "graph/nodeId.hpp"

namespace graph {

class Operator : public Schema {
public:
    Operator() : Schema("graph::operator", GraphdevNodeOperator) {
        addProperty("operator::op", std::string());

        addInput("a", nullptr);
        addInput("b", nullptr);

        addOutput("out", nullptr);
    }
};

class OperatorNode {
public:
    OperatorNode(Node* node) : _node(node) {}

    bool isValid() const { return _node->typeId() == GraphdevNodeOperator; }

    const void setOperator(const std::string& op) {
        _node->setProperty("operator::op", op);
    }

    const std::string getOperator() const {
        const auto& prop = _node->getProperty("operator::op");

        return std::get<std::string>(prop.value);
    }

private:
    Node* _node;
};

}