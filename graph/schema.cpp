#include "graph/schema.hpp"
#include "graph/node.hpp"

namespace graph {

bool Schema::addProperty(const std::string& name, const Property::ValueType& value) {
    _properties.emplace_back(name, value);
    return true;
}

bool Schema::addInput(const std::string& name, const Type* type) {
    _inputs.emplace_back(name, type);
    return true;
}

bool Schema::addOutput(const std::string& name, const Type* type){
    _outputs.emplace_back(name, type);
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

    for (const auto& input : _inputs) {
        node->createInput(input.first, input.second);
    }

    for (const auto& output : _outputs) {
        node->createOutput(output.first, output.second);
    }

    node->_schema = this;

    return true;
}

}