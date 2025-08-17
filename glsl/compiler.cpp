#include "glsl/compiler.hpp"

#include "graph/nodeId.hpp"
#include "graph/attribute.hpp"
#include "graph/struct.hpp"
#include "graph/operator.hpp"

#include "glsl/flags.hpp"

namespace glsl {

void Compiler::setPlatformLookup(const std::string& genericName, const std::string& platformName) {
    _platformLookups[genericName] = platformName;
}

std::string Compiler::compile(const graph::Program& program, const std::string& entryPoint) {
    _identifier_counter = 0;
    _nodeText.clear();

    auto* userFunc = program.getUserFunction(entryPoint);
    if (!userFunc) {
        return {};
    }

    _parseUserFunc(userFunc);

    return _text.str();
}

void Compiler::_parseUserFunc(const graph::UserFunction* func) {
    _text << (func->returnType ? func->returnType->name() : "void");
    _text << ' ' << func->name << '(';

    for (size_t i = 0; i < func->parameters.size(); i++) {
        const auto& param = func->parameters[i];

        if (i > 0) {
            _text << ", ";
        }

        switch (param.flags)
        {
        case glsl::GlslFunctionParameterFlagIn:
            _text << "in ";
            break;

        case glsl::GlslFunctionParameterFlagOut:
            _text << "out ";
        
        default:
            break;
        }

        _text << param.type->name() << ' ' << param.name;
    }

    _text << ") {" << std::endl;

    if (func->exitNode) {
        _parseNode(func->exitNode);
    }

    _text << "}";
}

void Compiler::_parseNode(const graph::Node* node) {
    for (const auto& input : node->inputs()) {
        if (input.connection) {
            _parseNode(input.connection->fromNode);
        }
    }

    if (node->flags & graph::NodeFlags::PlatformDependant) {
        // todo: if not present throw exception
        _nodeText[node] = _platformLookups[node->name()];
        return;
    }

    switch (node->typeId()) {
        case graph::GraphdevNodeStruct:
            _parseStruct(node);
            break;

        case graph::GraphdevNodeAttribute:
            _parseAttribute(node);
            break;

        case graph::GraphdevNodeOperator:
            _parseOperator(node);
            break;
    }
}

void Compiler::_parseStruct(const graph::Node* node) {
    const auto* in_connection = node->inputs()[0].connection;
    const bool nodeDefinedInScope = node->flags & graph::NodeFlags::NodeFlagDefinedInScope;
    const std::string typeName = graph::StructNode(node).getTypeName();

    if (in_connection) {
        // if the node is defined in this scope then we want to assign it;
        if (nodeDefinedInScope) {
            _text << node->name() << " = " << _nodeText[in_connection->fromNode] << ';' << std::endl;
            _nodeText[node] = node->name();
        } else { // we need to define a new variable and assign
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << typeName << ' ' << nodeName << " = " << _nodeText[in_connection->fromNode] << std::endl;
            _nodeText[node] = nodeName;
        }
    } else { // this is a leaf node and we simply want to output its values
        if (nodeDefinedInScope) {
            _nodeText[node] = node->name();
        } else {
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << typeName << ' ' << nodeName << " = " << typeName << '(';
            size_t propIndex = 0;
            for (const auto& property : node->properties()) {
                // filter out properties that do not belong to this struct
                if (property.name.find("::") != std::string::npos) {
                    continue;
                }

                if (propIndex > 0) {
                    _text << ", ";
                }

                std::visit([this](auto&& arg){
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, float>){
                        _text << arg;
                    }
                }, property.value);
                
                propIndex += 1;
            }
            _text << ");" << std::endl;
            _nodeText[node] = nodeName;
        }
    }
}

void Compiler::_parseAttribute(const graph::Node* node) {
    graph::AttributeNode attribute(const_cast<graph::Node*>(node));

    const auto* in_connection = node->inputs()[0].connection;

    _nodeText[node] = _nodeText[in_connection->fromNode] + "." + attribute.getAttribute();
}

void Compiler::_parseOperator(const graph::Node* node) {
    const graph::Node* operand_a = node->inputs()[0].connection->fromNode;
    const graph::Node* operand_b = node->inputs()[1].connection->fromNode;

    graph::OperatorNode operatorNode(const_cast<graph::Node*>(node));

    std::string operatorText = _nodeText[operand_a];
    operatorText.append(" ");
    operatorText.append(operatorNode.getOperator());
    operatorText.append(" ");
    operatorText.append(_nodeText[operand_b]);

    _nodeText[node] = std::move(operatorText);
}


}