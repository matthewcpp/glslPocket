#pragma once

#include "graphdev/connection.hpp"
#include "graphdev/type.hpp"

#include <vector>

namespace graphdev {

enum NodeFlags {
    NodeFlagNone = 0,

    /** This node's name is defined in the current scope.
     *  An example of this would be a function parameter or global variable */
    NodeFlagDefinedInScope = 1 << 0
};

class Node {
public:
    struct Port {
        Port() = default;
        Port(const std::string& name, const Type* type) : name(name), type(type) {}

        std::string name;
        const Type* type;
        const Connection* connection = nullptr;
    };

public:
    Node(uint32_t type_id, const std::string& name): _name(name), _type_id(type_id) {}
    virtual ~Node() = default;

    inline const uint32_t typeId() const { return _type_id; }
    inline const std::string& name() const { return _name; }
    const std::vector<Port>& outputs() const { return _outputs; }
    const std::vector<Port>& inputs() const { return _inputs; }

    virtual void setInputConnection(size_t index, const Connection* connection) {
        _inputs[index].connection = connection;
    }

    virtual void setOutputConnection(size_t index, const Connection* connection) {
        _outputs[index].connection = connection;
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
    uint32_t _type_id;
    std::string _name;
    std::vector<Port> _inputs;
    std::vector<Port> _outputs;
};

}