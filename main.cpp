
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
    graphdev::shadertoy::Shader shader;

    graphdev::Graph& graph = shader.mainImage->graph;

    auto* colorNode = dynamic_cast<graphdev::glsl::Vec*>(graph.createNode("glsl::vec4"));
    //colorNode->setValue({0.1f, 0.85f, 0.1f, 1.0f});
    auto* fragColorNode = graph.findNodeByName("fragColor");

    auto* resolutionNode = dynamic_cast<graphdev::glsl::Vec*>(graph.createNode("shadertoy::iResolution"));
    auto* swizzleNode = dynamic_cast<graphdev::glsl::Swizzle*>(graph.createNode("glsl::swizzle"));
    graphdev::glsl::SwizzleEditor swizzleEditor(swizzleNode, graph);
    swizzleEditor.setMask("xy");
    graph.connect(resolutionNode, 0, swizzleNode, 0);

    auto* fragCoordNode = graph.findNodeByName("fragCoord");
    auto* divideNode = dynamic_cast<graphdev::glsl::Operator*>(graph.createNode("glsl::divide"));
    graph.connect(fragCoordNode, 0, divideNode, static_cast<uint32_t>(graphdev::glsl::Operator::InputPortIndex::A));
    graph.connect(swizzleNode, 0, divideNode, static_cast<uint32_t>(graphdev::glsl::Operator::InputPortIndex::B));
    auto* uvNode = dynamic_cast<graphdev::glsl::Vec*>(graph.createNode("glsl::vec2"));
    graph.connect(divideNode, 0, uvNode, 0);

    auto cosNode = dynamic_cast<graphdev::glsl::Builtin*>(graph.createNode("glsl::cos"));
    graph.connect(uvNode, 0, cosNode, 0);
    graph.connect(cosNode, 0, fragColorNode, 0);

    // graph.connect(uvNode, 0, fragColorNode, 0);
    
    std::cout << shader.compile() << std::endl;

    return 0;
}
