//
// Created by bogdan on 16.11.2023.
//
#pragma once
#include "ArrayList.hpp"

namespace amstl {
    template<typename T>
    class Hole final: private amstl::ArrayList<T> {
    private:
        amstl::ArrayList<T> list;
    public:
        void add(const T& value) {
            list.pushBack(value);
        }
        inline int32_t size() {
            return list.size();
        }
    };
}