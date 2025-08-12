#pragma once

#include "graph/program.hpp"

#include <filesystem>
#include <memory>

namespace graph {

class JsonWriter {
public:
    bool write(const Program& program, const std::filesystem::path path, bool prettyPrint);

};

}