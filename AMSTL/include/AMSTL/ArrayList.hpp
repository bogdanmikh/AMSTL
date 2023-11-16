#pragma once

#include <iostream>
#include <cassert>

namespace amstl {
    template<typename T>
    class ArrayList {
    private:
        uint32_t m_size;
        uint32_t m_reserve;
        const uint32_t reserve_start = 10;
        T *data;


        T *dataClone() {
            T *data_clone = new T[m_reserve];
            for (int i = 0; i < m_size - 1; i++) {
                data_clone[i] = data[i];
            }
            return data_clone;
        }

        void recreateArray() {
            T *data_clone = dataClone();
            delete[] data;
            data = new T[m_reserve];
            for (int i = 0; i < m_size; ++i) {
                data[i] = data_clone[i];
            }
        }

    public:
        inline ArrayList() : m_size(0) {
            m_reserve = reserve_start;
            data = new T[m_reserve];
        }

        // возращает кол-во текущих элементов
        inline int size() {
            return m_size;
        }

        // добавляет в конец массива элемент
        void pushBack(const T &Val) {
            if (++m_size <= m_reserve) {
                data[m_size - 1] = Val;
            } else {
                m_reserve += m_size;
                reserve(m_reserve);
                recreateArray();
                data[m_size++] = Val;
            }
        }

        // добавляет в начало массива элемент
        void pushFront(const T &Val) {
            if (++m_size <= m_reserve) {
                for (int i = m_size - 1; i > 0; i--) {
                    data[i] = data[i - 1];
                }
                data[0] = Val;
                return;
            }
            m_reserve += m_size;
            reserve(m_reserve);
            recreateArray();
            for (int i = m_size - 1; i > 0; i--) {
                data[i] = data[i - 1];
            }
            data[0] = Val;
        }

        // оператор возращения значения
        T &operator[](uint32_t i) {
            assert(i >= 0 && i < m_size);
            return data[i];
        }

        // удаляет из конца элемент
        void popBack() {
            if (m_size == 0) return;
            m_size--;
        }

        // возвращает 1 элемент
        inline T begin() {
            return (m_size != 0) ? data[0] : T{};
        }

        // возвращает _size-ный элемент    
        inline T last() {
            return data[m_size - 1];
        }

        // удаляет определенный элемент в списке
        void erase(const int &index) {
            T *data_clone = dataClone();
            m_size--;
            delete[] data;
            T *data = new T[m_reserve];
            for (int i = 0; i < m_size; i++) {
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
            m_reserve = reserve_start;
            m_size = 0;
            T *data = new T[m_reserve];
        }

        // задает кол-во элементов в список
        void resize(const int &res) {
            T *data_clone = dataClone();
            delete[] data;
            T *data = new T[res];
            for (int i = 0; i < (m_size < res) ? m_size : res; i++) {
                data[i] = data_clone[i];
            }
            m_size = res;
            delete[] data_clone;
        }

        inline void reserve(const uint32_t newReserve) {
            m_reserve = newReserve;
        }

        // возращает true если список пустой
        inline bool isEmpty() {
            return (m_size == 0);
        }

        // выводит список
        void printList() {
            for (int i = 0; i < m_size; i++) {
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
