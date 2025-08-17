#pragma once

#include "graph/node.hpp"
#include "graph/property.hpp"
#include "graph/schema.hpp"
#include "graph/nodeId.hpp"

namespace graph {

class Value : public Schema {
public:
    Value() : Schema("graph::value", GraphdevNodeValue) {
        addProperty("value::value", Property::ValueType());

        addInput("in", nullptr);
        addOutput("out", nullptr);
    }

};

class ValueNode {
public:
    ValueNode(Node* node) : _node(node) {}

    bool isValid() const { return _node->typeId() == GraphdevNodeValue; }

    void setValue(const Property::ValueType& value) {
        _node->setProperty("value::value", value);
    }

    std::string getTypeName() const {
        const auto& property = _node->getProperty("value::value");
        const auto typeIndex = static_cast<Property::TypeIndex>(property.value.index());

        switch (typeIndex) {
            case Property::TypeIndex::Float:
                return "float";

            case Property::TypeIndex::String:
                return "string";
        }

        return "unknown";
    }

    std::string getValueAsString() const {
        const auto& property = _node->getProperty("value::value");
        std::string result;

        std::visit([&property, &result](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::string>) {
                result = std::get<std::string>(property.value);
            } else {
                result = std::to_string(arg);
            }
        }, property.value);

        return result;
    }

private:
    Node* _node;
};

}