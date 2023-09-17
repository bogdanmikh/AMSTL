#pragma once

#include <iostream>
#include <vector>

namespace amstl {
    
    template<typename K, typename V>
    class govnoMap {
    private:
        std::vector<K> keys;
        std::vector<V> values;
    public:
        V& operator[](const K& key) {
            for (int i = 0; i < keys.size(); i++) {
                if (keys[i] == key) {
                    return values[i];
                }
            }
            keys.push_back(key);
            values.push_back(V());
            return values[values.size() - 1];
        }

        bool hasValue(const K& key) {
            for (int i = 0; i < keys.size(); i++) {
                if (keys[i] == key) return true;
            }
            return false;
        }
    };
}