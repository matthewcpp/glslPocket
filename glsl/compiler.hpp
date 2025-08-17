#pragma once

#include "graph/program.hpp"

#include <string>
#include <sstream>

namespace glsl {

class Float;
class Vec;
class Builtin;
class Operator;
class Swizzle;

// https://shadertoyunofficial.wordpress.com/2016/07/20/special-shadertoy-features/

class Compiler {
public:
    std::string compile(const graph::Program& program, const std::string& entryPoint);

    void setPlatformLookup(const std::string& genericName, const std::string& platformName);

private:

    void _parseUserFunc(const graph::UserFunction* func);

    void _parseNode(const graph::Node* node);
    void _parseStruct(const graph::Node* node);
    void _parseAttribute(const graph::Node* node);
    void _parseOperator(const graph::Node* node);

private:
    const graph::Program* _program;
    std::ostringstream _text;
    std::unordered_map<const graph::Node*, std::string> _nodeText;
    std::unordered_map<std::string, std::string> _platformLookups;
    uint32_t _identifier_counter;
};

}