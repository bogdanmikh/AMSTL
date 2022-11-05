#pragma once

#include <iostream>
#include <cassert>

namespace amstl {
template <typename T>
    class ArrayList {
    private:
        uint32_t size_t;
        uint32_t reserve_t;
        const uint32_t reserve_start = 10;
        T *data;

    public:
        inline ArrayList() : size_t(0) {
            reserve_t = reserve_start;
            data = new T[reserve_t];
        }
        // возращает кол-во текущих элементов
        inline int size() {
            return size_t;
        }          
        // добавляет в конец массива элемент
        void push_back(const T &Val) {
            if (++size_t <= reserve_t) {
                data[size_t - 1] = Val;
            } else {
                reserve_t += size_t;
                reserve(reserve_t);
                data[size_t++] = Val;
            }
        }
        // оператор возращения значения 
        T& operator [] (uint32_t i) {
            assert(i >=0 && i < size_t);
            return data[i];
        }
        // добавляет в конец массива элемент
        void push_front(const T &Val) {
            if (++size_t <= reserve_t) {
                for (int i = size_t - 1; i > 0; i--) {
                    data[i] = data[i - 1];
                }
                data[0] = Val;
            } else {
                reserve_t += size_t;
                reserve(reserve_t);
                for (int i = size_t - 1; i > 0; i--) {
                    data[i] = data[i - 1];
                }
                data[0] = Val;
            }
        }
        // удаляет из конца элемент
        void pop_back() {
            if (size_t == 0) return;
            T *data_clone = new T[reserve_t];
            for (int i = 0; i < size_t - 1; i++) {
                data_clone[i] = data[i];
            }
            size_t--;
            delete[] data;
            T *data = new T[reserve_t];
            for (int i = 0; i < size_t; i++) {
                data[i] = data_clone[i];
            }
            delete[] data_clone;
        }
        // возвращает 1 элемент    
        inline T begin() {
            return (size_t != 0) ? data[0] : T 
        }        
        // возвращает size-ный элемент    
        inline T last() {
            return data[size_t - 1];
        }           
        // удаляет определенный элемент в списке
        void erase(const int &index) {
            T *data_clone = new T[reserve_t];
            for (int i = 0; i < size_t - 1; i++) {
                data_clone[i] = data[i];
            }
            size_t--;
            delete[] data;
            T *data = new T[reserve_t];
            for (int i = 0; i < size_t; i++) {
                if (i == index) {
                    continue;
                } else if (i > index) {
                    data[i - 1] = data_clone[i];
                } else {
                    data[i] = data_clone[i];
                }
            }
            delete[] data_clone;
        }
        // очищает список 
        inline void clear() {
            delete[] data;
            reserve_t = reserve_start;
            size_t = 0;
            T *data = new T[reserve_t];
        }        
        // задает кол-во элементов в список
        void reserve(const int &res) {
            T *data_clone = new T[size_t];
            for (int i = 0; i < size_t; i++) {
                data_clone[i] = data[i];
            }
            reserve_t = res;
            delete[] data;
            T *data = new T[reserve_t];
            for (int i = 0; i < size_t; i++) {
                data[i] = data_clone[i];
            }
            delete[] data_clone;
        }
        // возращает true если список пустой
        inline bool is_empty() {
            return (size_t == 0) ? true : false;
        }
        // выводит список
        void print_list() {
            for (int i = 0; i < size_t; i++) {
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }
        // удаляет список
        inline ~ArrayList() {
            delete[] data;
        }
    };
}
