#include "graph/node.hpp"

#include "graph/schema.hpp"

namespace graph {

bool Node::setProperty(const std::string& name, Property::ValueType value) {
    auto result = std::find_if(_properties.begin(), _properties.end(), [&name](const Property& p) {
        return p.name == name;
    });

    if (result == _properties.end()) {
        return false;
    }

    auto& p = *result;
    if (p.value.index() != value.index()) {
        return false;
    }

    p.value = value;

    return true;
}

const Property& Node::getProperty(const std::string& name) {
    auto result = std::find_if(_properties.begin(), _properties.end(), [&name](const Property& p) {
        return p.name == name;
    });

    return result != _properties.end() ? *result : Property::invalid();
}

std::string Node::toString() const {
    std::string str;
    str.append("Node: ").append(_name).append(" [").append(_schema->name()).append("] (").append(std::to_string(_uniqueId)).append(")");
    return str;
}

}