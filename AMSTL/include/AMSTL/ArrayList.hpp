#pragma once

#include <iostream>
#include <cassert>

namespace amstl {
template <typename T>
    class ArrayList {
    private:
        uint32_t _size;
        uint32_t reserve_t;
        const uint32_t reserve_start = 10;
        T *data;

    public:
        inline ArrayList() : _size(0) {
            reserve_t = reserve_start;
            data = new T[reserve_t];
        }
        // возращает кол-во текущих элементов
        inline int size() {
            return _size;
        }          
        // добавляет в конец массива элемент
        void pushBack(const T &Val) {
            if (++_size <= reserve_t) {
                data[_size - 1] = Val;
            } else {
                reserve_t += _size;
                reserve(reserve_t);
                data[_size++] = Val;
            }
        }
        // добавляет в начало массива элемент
        void pushFront(const T &Val) {
            if (++_size <= reserve_t) {
                for (int i = _size - 1; i > 0; i--) {
                    data[i] = data[i - 1];
                }
                data[0] = Val;
            } else {
                reserve_t += _size;
                reserve(reserve_t);
                for (int i = _size - 1; i > 0; i--) {
                    data[i] = data[i - 1];
                }
                data[0] = Val;
            }
        }
        // оператор возращения значения 
        T& operator [] (uint32_t i) {
            assert(i >=0 && i < _size);
            return data[i];
        }
        // удаляет из конца элемент
        void popBack() {
            if (_size == 0) return;
            T *data_clone = new T[reserve_t];
            for (int i = 0; i < _size - 1; i++) {
                data_clone[i] = data[i];
            }
            _size--;
            delete[] data;
            T *data = new T[reserve_t];
            for (int i = 0; i < _size; i++) {
                data[i] = data_clone[i];
            }
            delete[] data_clone;
        }
        // возвращает 1 элемент    
        inline T begin() {
            return (_size != 0) ? data[0] : T;
        }        
        // возвращает _size-ный элемент    
        inline T last() {
            return data[_size - 1];
        }           
        // удаляет определенный элемент в списке
        void erase(const int &index) {
            T *data_clone = new T[reserve_t];
            for (int i = 0; i < _size - 1; i++) {
                data_clone[i] = data[i];
            }
            _size--;
            delete[] data;
            T *data = new T[reserve_t];
            for (int i = 0; i < _size; i++) {
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
            _size = 0;
            T *data = new T[reserve_t];
        }        
        // задает кол-во элементов в список
        void resize(const int &res) {
            T *data_clone = new T[_size];
            for (int i = 0; i < _size; i++) {
                data_clone[i] = data[i];
            }
            delete[] data;
            T *data = new T[res];
            for (int i = 0; i < res; i++) {
                data[i] = data_clone[i];
            }
            delete[] data_clone;
        }
        // возращает true если список пустой
        inline bool isEmpty() {
            return (_size == 0) ? true : false;
        }
        // выводит список
        void printList() {
            for (int i = 0; i < _size; i++) {
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }
        // деструктор
        inline ~ArrayList() {
            delete[] data;
        }
    };

}
