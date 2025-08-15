#include "glsl/compiler.hpp"

#include "graph/nodeId.hpp"
#include "graph/struct.hpp"

#include "glsl/flags.hpp"

namespace glsl {

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

    switch (node->typeId()) {
        case graph::GraphdevNodeStruct:
        _parseStruct(node);
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

#if 0
void Compiler::_parseFloat(const glsl::Float* node) {
    const auto* connection = node->inputs()[0].connection;

    if (connection) { //declare variable?
        _nodeText[node] = _nodeText[connection->fromNode];
    } else {

        _nodeText[node] = std::to_string(std::get<float>(node->properties()[0].value));
    }
}

void Compiler::_parseVec(const glsl::Vec* node) {
    const auto* in_connection = node->inputs()[0].connection;
    const bool nodeDefinedInScope = node->flags & graph::NodeFlags::NodeFlagDefinedInScope;

    if (in_connection) {
        // if the node is defined in this scope then we want to assign it;
        if (nodeDefinedInScope) {
            _text << node->name() << " = " << _nodeText[in_connection->fromNode] << ';' << std::endl;
            _nodeText[node] = node->name();
        } else { // we need to define a new variable and assign
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << "vec" << node->getSize() << ' ' << nodeName << " = " << _nodeText[in_connection->fromNode] << std::endl;
            _nodeText[node] = nodeName;
        }
    } else { // this is a leaf node and we simply want to output its values
        if (nodeDefinedInScope) {
            _nodeText[node] = node->name();
        } else {
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << "vec" << node->getSize() << ' ' << nodeName << " = vec" << node->getSize() << '(';
            for (size_t i = 0; i < node->properties().size(); i++) {
                const auto& property = node->properties()[i];
                if (i > 0) {
                    _text << ", ";
                }

                _text << std::get<float>(property.value);
            }
            _text << ");" << std::endl;
            _nodeText[node] = nodeName;
        }
    }
}

 void Compiler::_parseBuiltin(const glsl::Builtin* node) {
    std::string functionText = node->functionName();
    functionText.append("(");
    for (size_t i = 0; i < node->inputs().size(); i++) {
        const auto& input = node->inputs()[i];
        if (i > 0) {
            functionText.append(", ");
        }

        functionText.append(_nodeText[input.connection->fromNode]);
    }
    functionText.append(")");

    _nodeText[node] = std::move(functionText);
 }

void Compiler::_parseOperator(const glsl::Operator* node) {
    std::string operatorText = _nodeText[node->inputs()[static_cast<uint32_t>(glsl::Operator::InputPortIndex::A)].connection->fromNode];
    operatorText.append(" ");
    switch (node->type()) {
        case glsl::Operator::Type::Add:
            operatorText.append("+");
            break;
        case glsl::Operator::Type::Subtract:
            operatorText.append("-");
            break;
        case glsl::Operator::Type::Multiply:
            operatorText.append("*");
            break;
        case glsl::Operator::Type::Divide:
            operatorText.append("/");
            break;
    }
    operatorText.append(" ");
    operatorText.append(_nodeText[node->inputs()[static_cast<uint32_t>(glsl::Operator::InputPortIndex::B)].connection->fromNode]);

    _nodeText[node] = std::move(operatorText);
}

void Compiler::_parseSwizzle(const glsl::Swizzle* node) {
    const auto* in_connection = node->inputs()[0].connection;

    if (in_connection) { // recursively satify all dependnecies of this node
        _parseNode(in_connection->fromNode);
    }

    std::string swizzleText = _nodeText[in_connection->fromNode];
    swizzleText.append(".");
    swizzleText.append(node->mask());

    _nodeText[node] = std::move(swizzleText);
}
#endif

}