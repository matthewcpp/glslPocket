#include "graph/schema.hpp"
#include "graph/node.hpp"

namespace graph {

bool Schema::addProperty(const std::string& name, const Property::ValueType& value) {
    _properties.emplace_back(name, value);
    return true;
}

bool Schema::apply(Node* node) const {
    // currently nodes can only have one schema

    if (node->schema()) {
        return false;
    }
    node->setTypeId(_nodeTypeId);

    for (const auto& prop : _properties) {
        node->addProperty(prop.name, prop.value);
    }

    // temp: need to figure this out more:
    node->createInput("in", nullptr);
    node->createOutput("out", nullptr);

    node->_schema = this;

    return true;
}

}