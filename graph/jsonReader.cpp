#include "graph/jsonReader.hpp"

#include <fstream>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace graph {

class JsonReader::Context {
public:
    Context(Program& program) : program(program) {}

    Program& program;
    json document;
    std::vector<Node*> nodes;
};

JsonReader::JsonReader() = default;
JsonReader::~JsonReader() = default;

bool JsonReader::load(Program& program, const std::filesystem::path path) {
    std::ifstream file(path);

    if (!file) {
        return false;
    }

    json data = json::parse(file);

    _context = std::make_unique<Context>(program);
    _context->document = std::move(data);

    parseFunctions();

    return true;
}

void JsonReader::parseFunctions() {
    for (const auto& function : _context->document["functions"]) {
        auto functionName = function["name"].get<std::string>();

        UserFunction* userFunction = _context->program.createUserFunction(functionName);

        const auto& params = function["parameters"];
        for (const auto& param : params) {
            auto paramName = param["name"].get<std::string>();
            auto paramType = param["type"].get<std::string>();
            auto paramFlags = param["flags"].get<uint32_t>();

            userFunction->createParameter(paramName, paramType, paramFlags);
        }

        const auto& nodes = function["nodes"];
        _context->nodes.reserve(nodes.size());

        for (const auto& node : nodes) {
            auto nodeName = node["name"].get<std::string>();
            auto nodeSchema = node["schema"].get<std::string>();
            auto nodeFlags = node["flags"].get<uint32_t>();

            auto* graphNode = userFunction->graph.createNode(nodeSchema, nodeName);
            graphNode->flags = nodeFlags;

            if (node.contains("properties")) {
                const auto& jsonProperties = node["properties"];
                for (const auto& graphNodeProp : graphNode->properties()) {
                    std::visit([&graphNode, &graphNodeProp, &jsonProperties](auto&& arg){
                        auto jsonProp = jsonProperties.find(graphNodeProp.name);
                        if (jsonProp == jsonProperties.end()) {
                            return;
                        }

                        using T = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_same_v<T, float>){
                            graphNode->setProperty(graphNodeProp.name, jsonProp.value().get<float>());
                        } else if constexpr (std::is_same_v<T, std::string>) {
                            graphNode->setProperty(graphNodeProp.name, jsonProp.value().get<std::string>());
                        }
                    }, graphNodeProp.value);
                }
            }

            _context->nodes.emplace_back(graphNode);
        }

        auto exitNode = function["exitNode"].get<size_t>();
        userFunction->exitNode = _context->nodes[exitNode];

        for (const auto& connection : function["connections"]) {
            Node* fromNode = _context->nodes[connection["fromNode"].get<size_t>()];
            auto fromPort = connection["fromPort"].get<size_t>();
            Node* toNode = _context->nodes[connection["toNode"].get<size_t>()];
            auto toPort = connection["toPort"].get<size_t>();

            userFunction->graph.connect(fromNode, fromPort, toNode, toPort);
        }
    }
}

}