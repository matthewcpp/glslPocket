#include "shadertoy/shader.hpp"

#include "graph/jsonReader.hpp"
#include "graph/jsonWriter.hpp"

#include "glsl/compiler.hpp"
#include "glsl/flags.hpp"
#include "glsl/module.hpp"
#include "shadertoy/module.hpp"

namespace shadertoy {


Shader::Shader () 
    : _nodeRegistry(_typeRegistry), program(_typeRegistry, _nodeRegistry)
{
    glslModuleInit(_typeRegistry, _nodeRegistry);
    shadertoyModuleInit(_typeRegistry, _nodeRegistry);
}

void Shader::createNew() {
    mainImage = program.createUserFunction("mainImage");

    mainImage->parameters.emplace_back("fragColor", _typeRegistry.getType("vec4"), glsl::GlslFunctionParameterFlagOut);
    mainImage->parameters.emplace_back("fragCoord", _typeRegistry.getType("vec2"), glsl::GlslFunctionParameterFlagIn);
    mainImage->initializeGraph();

    mainImage->exitNode = mainImage->graph.findNodeByName("fragColor");
}

bool Shader::load(const std::string& path){
    graph::JsonReader reader;
    return reader.load(program, path);
}

bool Shader::write(const std::string& path) {
    graph::JsonWriter writer;
    return writer.write(program, path, true);
}

std::string Shader::compile() {
    glsl::Compiler compiler;
    return compiler.compile(program, "mainImage");
}

}