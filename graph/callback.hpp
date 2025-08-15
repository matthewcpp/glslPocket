#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <vector>

namespace graph {

template <typename ...Args>
class Callback {
public:
    using Handle = uint32_t;
    typedef std::function<void(Args...)> FuncType;

    Handle add(FuncType func) {
        auto handle = next_handle++;
        callbacks.emplace_back(std::make_pair(handle, func));
        
        return handle;
    }

    void remove(Handle handle) {
        auto result = std::find_if(callbacks.begin(), callbacks.end(), [&handle](EntryType const & entry) {
            return entry.first == handle;
        });

        if (result != callbacks.end()) {
            callbacks.erase(result);
        }
    }

    void operator()(Args... args) {
        for (auto & callback : callbacks) {
            callback.second(args...);
        }
    }

    void clear() {
        callbacks.clear();
    }

private:
    typedef std::pair<Handle, FuncType> EntryType;
    std::vector<EntryType> callbacks;
    uint32_t next_handle = 0;
};

}