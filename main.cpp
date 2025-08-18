
#include "shadertoy/shader.hpp"
#include "glsl/nodeFactory.hpp"

#include "commands/commandProcessor.hpp"
#include "commands/createNode.hpp"
#include "commands/renameNode.hpp"
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
    glsl::NodeFactory nodeFactory;

    shader.program.hooks.nodeCreated.add(onNodeCreated);
    shader.program.hooks.nodeDeleted.add(onNodeDeleted);
    shader.program.hooks.connectionCreated.add(onConnectionCreated);

    shader.createNew();
    //shader.load("/Users/mlarocca/development/scratch/shadertoy_new.json");

    command::Processor commandProcessor;
    
    auto* fragColorNode = shader.mainImage->graph.findNodeByName("fragColor");
    auto* fragCoordNode = shader.mainImage->graph.findNodeByName("fragCoord");

    // Normalized pixel coordinates (from 0 to 1)
    // vec2 uv = fragCoord/iResolution.xy;
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "resolution"));
    graph::Node* resolution = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "swizzle"));
    graph::Node* swizzle = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::SetProperty(shader.mainImage, swizzle, "attribute::name", "xy"));
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, resolution, 0, swizzle, 0));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "divide"));
    graph::Node* divide = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, fragCoordNode, 0, divide, 0));
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, swizzle, 0, divide, 1));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "vec2"));
    graph::Node* uv = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::RenameNode(shader.mainImage, uv, "uv"));
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, divide, 0, uv, 0));
    

    // Time varying pixel color
    // vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "vec3"));
    graph::Node* vec3 = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::SetProperty(shader.mainImage, vec3, "y", 2.0f));
    commandProcessor.execute(new command::SetProperty(shader.mainImage, vec3, "z", 2.0f));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "swizzle"));
    swizzle = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::SetProperty(shader.mainImage, swizzle, "attribute::name", "xyx"));
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, uv, 0, swizzle, 0));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "add"));
    graph::Node* add = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, swizzle, 0, add, 0));
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, vec3, 0, add, 1));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "time"));
    graph::Node* time = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "add"));
    graph::Node* add2 = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, time, 0, add2, 0));
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, add, 0, add2, 1));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "cos"));
    graph::Node* cosNode = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, add2, 0, cosNode, 0));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "float"));
    graph::Node* floatNode = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::SetProperty(shader.mainImage, floatNode, "value::value", 0.5f));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "multiply"));
    graph::Node* multiply = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, floatNode, 0, multiply, 0));
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, cosNode, 0, multiply, 1));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "add"));
    graph::Node* add3 = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, floatNode, 0, add3, 0));
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, multiply, 0, add3, 1));
    commandProcessor.execute(new command::CreateNode(shader.mainImage, nodeFactory, "vec3"));
    graph::Node* col = shader.mainImage->graph.getNodeById(nodeFactory.lastCreatedId());
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, add3, 0, col, 0));
    commandProcessor.execute(new command::CreateConnection(shader.mainImage, col, 0, fragColorNode, 0));

    // Output to screen
    // fragColor = vec4(col,1.0);

    
    std::cout << shader.compile() << std::endl;
    shader.write("/Users/mlarocca/development/scratch/shadertoy_new_out.json");

    return 0;
}
