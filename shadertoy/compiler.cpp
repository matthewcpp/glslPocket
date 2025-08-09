#include "shadertoy/compiler.hpp"

#include "graphdev/nodeId.hpp"
#include "graphdev/enterNode.hpp"

#include "glsl/flags.hpp"
#include "glsl/nodeId.hpp"
#include "glsl/float.hpp"
#include "glsl/vec2.hpp"
#include "glsl/vec3.hpp"
#include "glsl/vec4.hpp"
#include "glsl/builtin.hpp"
#include "glsl/operator.hpp"
#include "glsl/swizzle.hpp"

namespace graphdev::shadertoy {

std::string Compiler::compile(Shader& shader) {
    _identifier_counter = 0;
    _nodeText.clear();

    _parseUserFunc(shader.mainImage);

    return _text.str();
}

void Compiler::_parseUserFunc(const UserFunction* func) {
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

    _parseNode(func->enterNode);

    _text << "}";
}

void Compiler::_parseNode(const Node* node) {
    for (const auto& input : node->inputs()) {
        if (input.connection) {
            _parseNode(input.connection->fromNode);
        }
    }

    switch (node->typeId()) {
        case graphdev::GraphdevNodeId::GraphdevNodeEnter:
            _parseNode(dynamic_cast<const graphdev::EnterNode*>(node)->targetNode);
            break;
        case glsl::GlslNodeId::GlslNodeFloat:
            _parseFloat(dynamic_cast<const glsl::Float*>(node));
            break;
        case glsl::GlslNodeId::GlslNodeVec2:
            _parseVec2(dynamic_cast<const glsl::Vec2*>(node));
            break;
        case glsl::GlslNodeId::GlslNodeVec3:
            _parseVec3(dynamic_cast<const glsl::Vec3*>(node));
            break;
        case glsl::GlslNodeId::GlslNodeVec4:
            _parseVec4(dynamic_cast<const glsl::Vec4*>(node));
            break;
        case glsl::GlslNodeId::GlslNodeBuiltin:
            _parseBuiltin(dynamic_cast<const glsl::Builtin*>(node));
            break;
        case glsl::GlslNodeId::GlslNodeOperator:
            _parseOperator(dynamic_cast<const glsl::Operator*>(node));
            break;
        case glsl::GlslNodeId::GlslNodeSwizzle:
            _parseSwizzle(dynamic_cast<const glsl::Swizzle*>(node));
            break;
    }
}

void Compiler::_parseFloat(const glsl::Float* node) {
    const auto* connection = node->inputs()[0].connection;

    if (connection) {
        _nodeText[node] = _nodeText[connection->fromNode];
    } else {
        _nodeText[node] = std::to_string(node->value());
    }
}

void Compiler::_parseVec2(const glsl::Vec2* node) {
    const auto* in_connection = node->inputs()[0].connection;
    const bool nodeDefinedInScope = node->flags & NodeFlags::NodeFlagDefinedInScope;

    if (in_connection) {
        // if the node is defined in this scope then we want to assign it;
        if (nodeDefinedInScope) {
            _text << node->name() << " = " << _nodeText[in_connection->fromNode] << ';' << std::endl;
            _nodeText[node] = node->name();
        } else { // we need to define a new variable and assign
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << "vec2 " << nodeName << " = " << _nodeText[in_connection->fromNode] << std::endl;
            _nodeText[node] = nodeName;
        }
    } else { // this is a leaf node and we simply want to output its values
        if (nodeDefinedInScope) {
            _nodeText[node] = node->name();
        } else {
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << "vec2 " << nodeName << " = vec2(" << node->value()[0] << ", " << node->value()[1]  << ");" << std::endl;
            _nodeText[node] = nodeName;
        }
    }
}

void Compiler::_parseVec3(const glsl::Vec3* node) {
    const auto* in_connection = node->inputs()[0].connection;
    const bool nodeDefinedInScope = node->flags & NodeFlags::NodeFlagDefinedInScope;

    if (in_connection) {
        // if the node is defined in this scope then we want to assign it;
        if (nodeDefinedInScope) {
            _text << node->name() << " = " << _nodeText[in_connection->fromNode] << ';' << std::endl;
            _nodeText[node] = node->name();
        } else { // we need to define a new variable and assign
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << "vec3 " << nodeName << " = " << _nodeText[in_connection->fromNode] << std::endl;
            _nodeText[node] = nodeName;
        }
    } else { // this is a leaf node and we simply want to output its values
        if (nodeDefinedInScope) {
            _nodeText[node] = node->name();
        } else {
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << "vec3 " << nodeName << " = vec3(" << node->value()[0] << ", " << node->value()[1] << ", " << node->value()[2] << ");" << std::endl;
            _nodeText[node] = nodeName;
        }
    }
}

void Compiler::_parseVec4(const glsl::Vec4* node) {
    const auto* in_connection = node->inputs()[0].connection;
    const bool nodeDefinedInScope = node->flags & NodeFlags::NodeFlagDefinedInScope;

    if (in_connection) {
        // if the node is defined in this scope then we want to assign it;
        if (nodeDefinedInScope) {
            _text << node->name() << " = " << _nodeText[in_connection->fromNode] << ';' << std::endl;
            _nodeText[node] = node->name();
        } else { // we need to define a new variable and assign
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << "vec4 " << nodeName << " = " << _nodeText[in_connection->fromNode] << std::endl;
            _nodeText[node] = nodeName;
        }
    } else { // this is a leaf node and we simply want to output its values
        if (nodeDefinedInScope) {
            _nodeText[node] = node->name();
        } else {
            std::string nodeName = node->name() + '_' + std::to_string(_identifier_counter++);
            _text << "vec4 " << nodeName << " = vec4(" << node->value()[0] << ", " << node->value()[1] << ", " << node->value()[2] << ", " << node->value()[3] << ");" << std::endl;
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

}