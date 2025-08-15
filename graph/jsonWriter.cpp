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
            nodeJson["schema"] = n->schema()->name();
            nodeJson["flags"] = n->flags;

            
            const auto& nodeProperties = n->properties();
            const auto& schemaProperties = n->schema()->properties();
            if (nodeProperties.empty()) {
                return;
            }

            json nodeJsonProps = json::object();
            for (size_t i = 0; i < nodeProperties.size(); i++) {
                const auto& property = nodeProperties[i];

                // filter out properties that have their default value.
                if (property == schemaProperties[i]) {
                    continue;
                }

                std::visit([&property, &nodeJsonProps](auto&& arg){
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, float>){
                        nodeJsonProps[property.name] = std::get<float>(property.value);
                    } else if constexpr (std::is_same_v<T, std::string>) {
                        nodeJsonProps[property.name] = std::get<std::string>(property.value);
                    }
                }, property.value);
                
            }

            if (!nodeJsonProps.empty()) {
                nodeJson["properties"] = nodeJsonProps;
            }
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