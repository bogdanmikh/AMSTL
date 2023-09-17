#pragma once

#include "LinkedList.hpp"
#include <iostream>
#include <vector>

namespace amstl {
    template<typename K, typename V>
    class HashMap {
        public:
        HashMap() {
            this->keys.resize(100);
        }

        V& operator[](const K& key) {
           int index = hash(key) % 100;
           LinkedList<Pair>& list = keys[index];
           for(int i = 0; i < list.size(); i++) {
               Pair& item = list[i];
               if(item.key == key) {
                   return item.value;
               }
           }
           list.pushBack(Pair());
           list[list.size() - 1].key = key;
           return list[list.size() - 1].value;
        }

        void put(const K& key, const V& val) {
            int index = hash(key) % 100;
            keys[index].pushBack(Pair());
            keys[index][keys[index].size() - 1].key = key;
            keys[index][keys[index].size() - 1].value = val;
        }
        private:
        class Pair {
        public:
            K key;
            V value;
        };
        V checkHash(const std::string& p) {
            int index = hash(p) % 100;
            V ans;
            for (int i = 0; i < keys[index].size(); i++) {
                if (keys[index][i].key == p) return keys[index][i].value;
            }
            Pair val;
            val.value = -1;
            return val.value;
        }
        V checkHash(const int& p) {
            int index = hash(p) % 100;
            for (int i = 0; i < keys[index].size(); i++) {
                if (keys[index][i].key == p) return keys[index][i].value;
            }
            Pair val;
            val.value = -1;
            return val.value;
        }
        std::vector<amstl::LinkedList<Pair>> keys;

        uint64_t convert(char x) {
            uint32_t p = uint32_t(x);
            uint64_t result = (((p * 120) + (p * p)) + 5) % 10;
            if (result == 0) result += 5;
            return result;
        }

        uint64_t convert(const K& x) {
            uint32_t p = uint32_t(x);
            uint64_t result = ((p * 120) + (p * p)) % 10;
            return result;
        }

        uint64_t hash(const std::string& p) {
            uint64_t ans;
            ans = convert(p[0]);
            for (int i = 1; i < p.size(); i++)  {
                ans *= 10;
                ans += convert(p[i]);
            }
            return ans;
        } 
        uint64_t hash(const int& p) {
            uint64_t ans = 0;
            uint64_t copyP = p;
            while (copyP >= 1) {
                ans += (copyP % 10);
                ans *= 10;
                copyP /= 10;
            }
            return ans;
        } 
    };
} 
