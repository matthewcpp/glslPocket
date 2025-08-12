#include "graph/jsonWriter.hpp"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace graph {

bool JsonWriter::write(const Program& program, const std::filesystem::path path, bool prettyPrint) {
    std::ofstream file(path);

    if (!file) {
        return false;
    }

    json doc = json::object();
    doc["functions"] = json::array();

    program.iterateUserFuncs([&doc](const UserFunction* userFunc){
        json& userFuncJson = doc["functions"].emplace_back(json::object());
        userFuncJson["name"] = userFunc->name;

        userFuncJson["parameters"] = json::array();
        json& userFuncParams = userFuncJson["parameters"];

        for (const auto& param : userFunc->parameters) {
            json& paramJson = userFuncParams.emplace_back(json::object());
            paramJson["name"] = param.name;
            paramJson["type"] = param.type->name();
            paramJson["flags"] = param.flags;
        }

        std::unordered_map<const Node*, size_t> nodeToIndex;
        json userFuncNodes = json::array();

        userFunc->graph.iterateNodes([&userFuncNodes, &nodeToIndex](const Node* n){
            nodeToIndex[n] = userFuncNodes.size();
            json& nodeJson = userFuncNodes.emplace_back(json::object());

            nodeJson["name"] = n->name();
            nodeJson["type"] = n->typeId();
            nodeJson["flags"] = n->flags;

            
            const auto& nodeProperties = n->properties();
            if (nodeProperties.empty()) {
                return;
            }

            json nodeJsonProps = json::object();
            for (const auto& property : nodeProperties) {
                nodeJsonProps[property.name] = std::get<float>(property.value);
            }

            nodeJson["properties"] = nodeJsonProps;
        });

        userFuncJson["nodes"] = userFuncNodes;
        userFuncJson["exitNode"] = nodeToIndex[userFunc->exitNode];

        userFuncJson["connections"] = json::array();
        json& connections = userFuncJson["connections"];
        userFunc->graph.iterateConnections([&connections, &nodeToIndex](const Connection* connection){
            json& connectionJson = connections.emplace_back(json::object());
            connectionJson["fromNode"] = nodeToIndex[connection->fromNode];
            connectionJson["fromPort"] = connection->fromPortIndex;
            connectionJson["toNode"] = nodeToIndex[connection->toNode];
            connectionJson["toPort"] = connection->toPortIndex;
        });
    });

    file << doc.dump(prettyPrint ? 4 : -1);

    return true;
}

}