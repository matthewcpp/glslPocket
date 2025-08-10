#include "graph/userFunction.hpp"

namespace graphdev {

bool UserFunction::initializeGraph() {
    for (const auto& param : parameters) {
        auto* paramNode = graph.createNodeForType(param.type->name());
        paramNode->setName(param.name);
        paramNode->flags |= NodeFlags::NodeFlagDefinedInScope;
    }

    if (returnType) {
        auto* returnNode = graph.createNodeForType(returnType->name());
        returnNode->setName("return");
    } else {
        enterNode = graph.createNode("graphdev::enter");
    }

    return true;
}

bool UserFunction::createParameter(const std::string& name, const std::string& typeName, uint32_t flags) {
    const Type* paramType = _typeRegistry.getType(typeName);
    if (!paramType) {
        return false;
    }

    // TODO: check for unique param name?
    parameters.emplace_back(name, paramType, flags);

    return true;
}

}