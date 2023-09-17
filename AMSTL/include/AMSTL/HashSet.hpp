#pragma once

#include "HashMap.hpp"

namespace amstl {
    template<typename T>
    class HashSet final {
    public:
        void insert(T value) {
            map.put(value, 0);
        }
    private:
        HashMap<T, int> map;
    };
}
