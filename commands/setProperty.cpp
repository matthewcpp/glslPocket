#include "commands/setProperty.hpp"

namespace command {

SetProperty::SetProperty(graph::UserFunction* userFunc, graph::Node* node, const std::string& name, const graph::Property::ValueType& value)
    : _userFunc(userFunc), _nodeId(node->uniqueId()), _propertyName(name), _newValue(value)
{
}

bool SetProperty::execute() {
    graph::Node* node = _userFunc->graph.getNodeById(_nodeId);

    const auto& property = node->getProperty(_propertyName);
    if (!property.isValid()) {
        return false;
    }

    _originalValue = property.value;

    return node->setProperty(_propertyName, _newValue);
}

}