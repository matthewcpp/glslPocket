#pragma once

#include "graph/connection.hpp"
#include "graph/property.hpp"
#include "graph/type.hpp"

#include <vector>

namespace graph {

class Schema;

/** A unique identifer for this node in it's graph. */
typedef uint32_t NodeUniqueId;

/** Identifier for the type of node.  
 *  Note this is different than the types of node connections, e.g scalar or vector. */
typedef uint32_t NodeTypeId;

enum NodeFlags {
    NodeFlagNone = 0,

    /** This node's name is defined in the current scope.
     *  An example of this would be a function parameter or global variable */
    NodeFlagDefinedInScope = 1 << 0
};

class Node {
public:
    struct InputPort {
        InputPort() = default;
        InputPort(const std::string& name, const Type* type) : name(name), type(type) {}

        std::string name;
        const Type* type;
        const Connection* connection = nullptr;
    };

    struct OutputPort {
        OutputPort() = default;
        OutputPort(const std::string& name, const Type* type) : name(name), type(type) {}

        std::string name;
        const Type* type;
        std::vector<const Connection*> connections;
    };

public:
    Node(NodeUniqueId uniqueId, const std::string& name)
        : _uniqueId(uniqueId), _name(name) {}

    const NodeUniqueId uniqueId() const {return _uniqueId; }
    const NodeTypeId typeId() const { return _typeId; }
    void setTypeId(uint32_t type) {  _typeId = type; }
    const std::string& name() const { return _name; }
    void setName(const std::string& name) { _name = name; }
    const Schema* schema() const {return _schema; }
    const std::vector<InputPort>& inputs() const { return _inputs; }
    const std::vector<OutputPort>& outputs() const { return _outputs; }
    const std::vector<Property>& properties() const { return _properties; }

    std::string toString() const;
    bool setProperty(const std::string& name, Property::ValueType value);
    const Property& getProperty(const std::string& name);

    uint32_t flags = NodeFlags::NodeFlagNone;

private:

    friend class Schema;
    friend class Graph;

    bool addProperty(const std::string& name, const Property::ValueType& value) {
        _properties.emplace_back(name, value);
        return true;
    }

    void createInput(const std::string& name, const Type* type) {
        _inputs.emplace_back(name, type);
    }
    void createOutput(const std::string& name, const Type* type) {
        _outputs.emplace_back(name, type);
    }

private:
    NodeUniqueId _uniqueId;
    NodeTypeId _typeId;
    const Schema* _schema = nullptr;
    std::string _name;
    std::vector<InputPort> _inputs;
    std::vector<OutputPort> _outputs;
    std::vector<Property> _properties;
};

}