//
// Created by bogdan on 02.09.2023.
//
#include <iostream>

#pragma once

namespace amstl {
    template<typename T>
    class BinaryTree {
    private:
        struct Node {
            Node(T value) :
                    value(value), left(nullptr), right(nullptr) {
            }

            T value;
            Node *left;
            Node *right;
        };

        void printTree(const Node* node) {
            if (!node) return;
            printTree(node->left);
            std::cout << node->value << " ";
            printTree(node->right);
        }

        void insert(Node* node) {
            size++;
            if (head == nullptr) {
                head = node;
                return;
            }
            Node *current = head;
            while (current->left != nullptr || current->right != nullptr) {
                if (node->value > current->value) {
                    if (current->right == nullptr) break;
                    current = current->right;
                } else {
                    if (current->left == nullptr) break;
                    current = current->left;
                }
            }
            if (node->value > current->value) {
                current->right = node;
            } else {
                current->left = node;
            }
        }

        void deleteAll(Node* node) {
            if (node == nullptr) return;
            deleteAll(node->left);
            deleteAll(node->right);
            delete node;
        }

        void remove(Node* node) {
            if (!node) return;
            if (node == head) {
                head = nullptr;
                delete node;
            } else {
                if (node->left) {
                    remove(node->left);
                }
                if (node->right) {
                    remove(node->right);
                }
                delete node;
            }
        }

        Node *head = nullptr;
        uint32_t size = 0;
    public:
        ~BinaryTree() {
            if (head == nullptr) return;
            clear();
        }

        void clear() {
            size = 0;
            deleteAll(head->left);
            deleteAll(head->right);
            delete head;
        }


        Node* find(const T& value) {
            if (head == nullptr) return false;
            Node *insertion = head;
            while (insertion->value != value) {
                if (value > insertion->value) {
                    if (insertion->right == nullptr) return nullptr;
                    insertion = insertion->right;
                } else {
                    if (insertion->left == nullptr) return nullptr;
                    insertion = insertion->left;
                }
            }
            if (value == insertion->value) {
                return insertion;
            }
            return nullptr;
        }

        void add(const T& value) {
            Node *node = new Node(value);
            if (head == nullptr) {
                head = node;
            } else {
                insert(node);
            }
        }

        void erase(const T& value) {
            Node* node = find(value);
            if (!node) return;
            remove(node);
        }

        void print() {
            printTree(head);
        }

        uint32_t getSize() {
            return size;
        }
    };
}

