#pragma once

#include "graph/program.hpp"

#include <filesystem>
#include <memory>

namespace graph {

class JsonReader {
public:
    JsonReader();
    ~JsonReader();

    bool load(Program& program, const std::filesystem::path path);

private:
    void parseFunctions();

private:
    class Context;
    std::unique_ptr<Context> _context;
};

}