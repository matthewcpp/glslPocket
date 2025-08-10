#pragma once

#include "graph/connection.hpp"
#include "graph/type.hpp"

#include <vector>

namespace graph {

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
    Node(NodeUniqueId uniqueId, NodeTypeId typeId, const std::string& name)
        : _uniqueId(uniqueId), _typeId(typeId), _name(name) {}
    virtual ~Node() = default;

    inline const NodeUniqueId uniqueId() const {return _uniqueId; }
    inline const NodeTypeId typeId() const { return _typeId; }
    inline const std::string& name() const { return _name; }
    const std::vector<InputPort>& inputs() const { return _inputs; }
    const std::vector<OutputPort>& outputs() const { return _outputs; }

    virtual void setInputConnection(size_t index, const Connection* connection) {
        _inputs[index].connection = connection;
    }

    virtual void addOutputConnection(size_t index, const Connection* connection) {
        _outputs[index].connections.push_back(connection);
    }

    virtual void setName(const std::string& name) {
        _name = name;
    }

    bool hasInputs() const {
        for (const auto& p : _inputs) {
            if (p.connection) {
                return true;
            }
        }

        return false;
    }

    uint32_t flags = NodeFlags::NodeFlagNone;

protected:
    void createInput(const std::string& name, const Type* type) {
        _inputs.emplace_back(name, type);
    }
    void createOutput(const std::string& name, const Type* type) {
        _outputs.emplace_back(name, type);
    }

protected:
    NodeUniqueId _uniqueId;
    NodeTypeId _typeId;
    std::string _name;
    std::vector<InputPort> _inputs;
    std::vector<OutputPort> _outputs;
};

}