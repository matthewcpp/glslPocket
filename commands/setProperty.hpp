#pragma once

#include "commands/command.hpp"

#include "graph/userFunction.hpp"

namespace command {

class SetProperty : public Command {
public:
    SetProperty(graph::UserFunction* userFunc, graph::Node* node, const std::string& name, const graph::Property::ValueType& value);

    virtual bool execute() override;

private:
    graph::UserFunction* _userFunc;
    graph::NodeUniqueId _nodeId;
    std::string _propertyName;
    graph::Property::ValueType _originalValue;
    graph::Property::ValueType _newValue;
};

}