#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace graphdev {

class Type {
public:
    Type(uint32_t id, const std::string& name) : _id(id), _name(name) {};

    inline const std::string& name() const { return _name; }
    inline const uint32_t id() const {return _id; }

private:
    uint32_t _id;
    std::string _name;
};

}