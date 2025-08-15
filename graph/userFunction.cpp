#include "graph/userFunction.hpp"

namespace graph {

bool UserFunction::initializeGraph() {
    for (const auto& param : parameters) {
        auto* paramNode = graph.createNodeForType(param.type);
        paramNode->setName(param.name);
        paramNode->flags |= NodeFlags::NodeFlagDefinedInScope;
    }

    if (returnType) {
        auto* returnNode = graph.createNodeForType(returnType);
        returnNode->setName("return");
    } else {
        exitNode = graph.createNode("graphdev::exit");
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