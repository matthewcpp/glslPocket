#include "shadertoy/shader.hpp"

#include "glsl/compiler.hpp"
#include "glsl/flags.hpp"
#include "glsl/module.hpp"
#include "shadertoy/module.hpp"

namespace graphdev::shadertoy {


Shader::Shader () 
    : _nodeRegistry(_typeRegistry), program(_typeRegistry, _nodeRegistry)
{
    glsl_module(_typeRegistry, _nodeRegistry);
    shadertoy_module(_typeRegistry, _nodeRegistry);

    mainImage = program.createUserFunction("mainImage");

    mainImage->parameters.emplace_back("fragColor", _typeRegistry.getType("vec4"), glsl::GlslFunctionParameterFlagOut);
    mainImage->parameters.emplace_back("fragCoord", _typeRegistry.getType("vec2"), glsl::GlslFunctionParameterFlagIn);
    mainImage->initializeGraph();

    mainImage->enterNode = mainImage->graph.findNodeByName("fragColor");
}

std::string Shader::compile() {
    glsl::Compiler compiler;
    return compiler.compile(program, "mainImage");
}

}