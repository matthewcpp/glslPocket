
#include "shadertoy/shader.hpp"

#include "glsl/vec.hpp"
#include "glsl/builtin.hpp"
#include "glsl/operator.hpp"
#include "glsl/swizzle.hpp"

#include "glsl/compiler.hpp"

#include <iostream>

enum NodeId {
    FragColor,
    Vec4
};

int main(int argc, char** argv) {
    shadertoy::Shader shader;

    graph::Graph& graph = shader.mainImage->graph;

    auto* colorNode = dynamic_cast<glsl::Vec*>(graph.createNode("glsl::vec4"));
    colorNode->setProperty("x", 0.1f);
    colorNode->setProperty("y", 0.85f);
    colorNode->setProperty("z", 0.1f);
    colorNode->setProperty("w", 1.0f);
    auto* fragColorNode = graph.findNodeByName("fragColor");
    graph.connect(colorNode, 0, fragColorNode, 0);
    std::cout << shader.compile() << std::endl;

    return 0;

    auto* resolutionNode = dynamic_cast<glsl::Vec*>(graph.createNode("shadertoy::iResolution"));
    auto* swizzleNode = dynamic_cast<glsl::Swizzle*>(graph.createNode("glsl::swizzle"));
    glsl::SwizzleEditor swizzleEditor(swizzleNode, graph);
    swizzleEditor.setMask("xy");
    graph.connect(resolutionNode, 0, swizzleNode, 0);

    auto* fragCoordNode = graph.findNodeByName("fragCoord");
    auto* divideNode = dynamic_cast<glsl::Operator*>(graph.createNode("glsl::divide"));
    graph.connect(fragCoordNode, 0, divideNode, static_cast<uint32_t>(glsl::Operator::InputPortIndex::A));
    graph.connect(swizzleNode, 0, divideNode, static_cast<uint32_t>(glsl::Operator::InputPortIndex::B));
    auto* uvNode = dynamic_cast<glsl::Vec*>(graph.createNode("glsl::vec2"));
    graph.connect(divideNode, 0, uvNode, 0);

    auto cosNode = dynamic_cast<glsl::Builtin*>(graph.createNode("glsl::cos"));
    graph.connect(uvNode, 0, cosNode, 0);
    graph.connect(cosNode, 0, fragColorNode, 0);

    // graph.connect(uvNode, 0, fragColorNode, 0);
    
    std::cout << shader.compile() << std::endl;

    return 0;
}
