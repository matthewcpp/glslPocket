
#include "shadertoy/shader.hpp"
#include "shadertoy/nodeFactory.hpp"

#include "commands/commandProcessor.hpp"
#include "commands/createNode.hpp"
#include "commands/setProperty.hpp"
#include "commands/createConnection.hpp"

#include <iostream>

enum NodeId {
    FragColor,
    Vec4
};

void onNodeCreated(graph::Node* node) {
    std::cout << "Created: " << node->toString() << std::endl;
}

void onNodeDeleted(graph::Node* node) {
    std::cout << "Deleted: " << node->toString() << std::endl;
}

void onConnectionCreated(graph::Connection* connection) {
    std::cout << "Created: " << connection->toString() << std::endl;
}

void onConnectionDeleted(graph::Connection* connection) {
    std::cout << "Deleted: " << connection->toString() << std::endl;
}

int main(int argc, char** argv) {
    shadertoy::Shader shader;
    shadertoy::NodeFactory nodeFactory;

    shader.program.hooks.nodeCreated.add(onNodeCreated);
    shader.program.hooks.nodeDeleted.add(onNodeDeleted);
    shader.program.hooks.connectionCreated.add(onConnectionCreated);

    shader.createNew();
    //shader.load("/Users/mlarocca/development/scratch/shadertoy_new.json");

    command::Processor commandProcessor;
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "vec4"));
    commandProcessor.undo();
    commandProcessor.redo();
    graph::Node* colorNode = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());

    commandProcessor.execute(new command::SetProperty(shader.mainImage, colorNode, "x", 0.1f));
    commandProcessor.execute(new command::SetProperty(shader.mainImage, colorNode, "y", 0.85f));
    commandProcessor.execute(new command::SetProperty(shader.mainImage, colorNode, "z", 0.1f));
    commandProcessor.execute(new command::SetProperty(shader.mainImage, colorNode, "w", 1.0f));
    
    auto* fragColorNode = shader.mainImage->graph.findNodeByName("fragColor");
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, colorNode, 0, fragColorNode, 0));

    /*
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
    */
    
    std::cout << shader.compile() << std::endl;
    shader.write("/Users/mlarocca/development/scratch/shadertoy_new_out.json");

    return 0;
}
