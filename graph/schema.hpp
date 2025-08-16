#pragma once

#include "graph/property.hpp"
#include "graph/type.hpp"

#include <vector>

namespace graph {

class Node;

class Schema {
public:
    Schema(const std::string& name, uint32_t nodeTypeId) : _name(name), _nodeTypeId(nodeTypeId) {}
    virtual ~Schema() = default;

public:
    const std::string& name() const { return _name; }
    const uint32_t nodeTypeId() const {return _nodeTypeId; }
    const std::vector<Property>& properties() const {return _properties; }

    bool addProperty(const std::string& name, const Property::ValueType& value);
    bool addInput(const std::string& name, const Type* type);
    bool addOutput(const std::string& name, const Type* type);
    bool apply(Node* node) const;

private:
    std::string _name;
    uint32_t _nodeTypeId;
    std::vector<Property> _properties;

    using PortInfo = std::pair<std::string, const Type*>;
    std::vector<PortInfo> _inputs;
    std::vector<PortInfo> _outputs;
};

}
