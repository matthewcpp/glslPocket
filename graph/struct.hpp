#pragma once

#include "graph/type.hpp"
#include "graph/schema.hpp"
#include "graph/nodeId.hpp"
#include "graph/node.hpp"

namespace graph {

class Struct : public Schema {
public:
    Struct(const Type* type, const std::string& name) : Schema(name, GraphdevNodeStruct), _type(type) {
        addProperty("struct::type", type->name());
    }

    const Type* type() const { return _type; }

private:
    const Type* _type;
};

class StructNode{
public:
    StructNode(const Node* node): _node(node) {}

    bool isValid() const {return _node->typeId() == GraphdevNodeStruct; }

    const std::string getTypeName() const {
        const auto& nodeProperties = _node->properties();
        const auto result = std::find_if(nodeProperties.begin(), nodeProperties.end(), [](const Property& p){
            return p.name == "struct::type";
        });

        return std::get<std::string>((*result).value);
    }

private:
    const Node* _node;
};

}