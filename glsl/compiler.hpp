#pragma once

#include "graphdev/program.hpp"

#include <string>
#include <sstream>

namespace graphdev::glsl {

class Float;
class Vec;
class Builtin;
class Operator;
class Swizzle;

}

namespace graphdev::glsl {

// https://shadertoyunofficial.wordpress.com/2016/07/20/special-shadertoy-features/

class Compiler {
public:
    std::string compile(const Program& program, const std::string& entryPoint);

private:
    void _parseUserFunc(const UserFunction* func);

    void _parseNode(const Node* node);
    void _parseFloat(const glsl::Float* node);
    void _parseVec(const glsl::Vec* node);

    void _parseBuiltin(const glsl::Builtin* node);
    void _parseOperator(const glsl::Operator* node);
    void _parseSwizzle(const glsl::Swizzle* node);

private:
    const Program* _program;
    std::ostringstream _text;
    std::unordered_map<const Node*, std::string> _nodeText;
    uint32_t _identifier_counter;
};

}