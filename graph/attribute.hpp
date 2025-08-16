#pragma once

#include "graph/schema.hpp"
#include "graph/node.hpp"
#include "graph/nodeId.hpp"

namespace graph {

class Attribute : public Schema {
public:
    Attribute() : Schema("graph::attribute", GraphdevNodeAttribute) {
        addProperty("attribute::name", std::string());
    }

};

class AttributeNode {
public:
    AttributeNode(Node* node) : _node(node) {}

    bool isValid() const { return _node->typeId() == GraphdevNodeAttribute; }

    void setAttribute(const std::string& name) {
        _node->setProperty("attribute::name", name);
    }

    std::string getAttribute() const {
        auto& property = _node->getProperty("attribute::name");
        return std::get<std::string>(property.value);
    }

private:
    Node* _node;
};

}