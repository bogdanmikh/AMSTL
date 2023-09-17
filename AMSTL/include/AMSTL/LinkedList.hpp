#pragma once

#include <iostream>
#include <cassert>

namespace amstl {

    template <typename T>
    class LinkedList {
        private:
        class Node {
            public:
            Node* next;
            T value;
        };
        uint32_t _size;
        Node* first;
        Node* last;
        public:
        inline LinkedList() {
            this->_size = 0;
            this->first = nullptr;
            this->last = nullptr;
        }
        // возвращает кол-во текущих элементов2
        inline uint32_t size() {
            return _size;
        } 
        // добавляет в конец массива элемент
        inline void pushBack(const T &val) {
            Node* k = new Node();
            _size++; 
            k->value = val;
            k->next = nullptr;
            if (first == nullptr) {
                first = k;
                last = k;
                return;
            } 
            last->next = k;
            last = k;
        }
        // добавляет в начало массива элемент
        void pushFront(const T &val) {
            Node* k = new Node();
            k->value = val;
            _size++;
            if (first == nullptr) {
                first = k;
                last = k;
                k->next = nullptr;
                return;
            }
            k->next = first;
            first = k;
        }
        // оператор возращения значения 
        T& operator [] (const uint32_t &i) {
            assert(i >= 0 && i < _size);
            Node* result = first; 
            for (int k = 1; k <= i; k++) {
                result = result->next;
            }
            return result->value;
        }
        // удаляет из конца элемент
        void popBack() {
            if (_size == 0) return;
            _size--;
            Node* result = first; 
            while (result->next != last) {
                result = result->next;
            }
            result->next = nullptr;
            delete last;
            last = result;
        }
        // возвращает 1 элемент    
        inline T begin() {
            return first->value;
        }
        // возвращает _size-ный элемент  
        inline T end() {
            return last->value;
        } 
        // очищает список 
        void clear() {
            Node* n = first;
            _size = 0;
            while (n->next != nullptr) {
                Node* h = n;
                n = h->next;
                delete h;
            }
            delete n;
            first = nullptr;
            last = nullptr;
        }
        // возращает true если список пустой
        inline bool isEmpty() {
            return (_size == 0) ? true : false;
        }

        std::pair<bool, T> isFinded(const T& val) {
            Node* result = first; 
            std::pair<bool, T> ans = {false, 0};
            if (first == nullptr) {
                return ans;
            }
            while (result->next != nullptr) {
                if (result->value == val) {
                    ans.first = true;
                    ans.second = result->value;
                }
            }
            return ans;
        }
        // выводит список
        void printList() {
            Node* result = first; 
            if (first == nullptr) return;
            while (result->next != nullptr) {
                std::cout << result->value << ' ';
                result = result->next;
            }
            std::cout << std::endl;
        }
        // деструктор
        ~LinkedList() {
            Node* n = first;
            if (first == nullptr) return;
            while (n->next != nullptr) {
                Node* h = n;
                n = n->next;
                delete h;
            }
            delete n;
        }
    };
}