//
// Created by bogdan on 02.09.2023.
//
#pragma once

#include <iostream>
#include <optional>

namespace amstl {
    template<typename K, typename V>
    class BinaryTree {
    private:
        struct Node {
        private:
        int32_t getHeight(Node *node) {
            return (node == nullptr) ? 0 : node->h;
        }
        public:
            Node(K key, V value) :
                    key(key)
                    , value(value)
                    , left(nullptr)
                    , right(nullptr)
                    , h(0) {
            }
            K key;
            V value;
            Node *left;
            Node *right;
            int32_t h;
            void updateHeight() {
                h = std::max(getHeight(left), getHeight(right)) + 1;
            }
            int32_t getBalance() {
                return getHeight(left) - getHeight(right);
            }
        };

        /// add node in tree
        Node* insert(Node* node, const K& key, const V& value) {
            if (node == nullptr) {
                return new Node(key, value);
            }
            if (key < node->key) {
                node->left = insert(node->left, key, value);
            } else if (key > node->key) {
                node->right = insert(node->right, key, value);
            }
            node = balancing(node);
            return node;
        }

        /// find element
        std::optional<Node*> find(const K& key) {
            if (head == nullptr) return {};
            Node *insertion = head;
            while (insertion->key != key) {
                if (key > insertion->key) {
                    if (insertion->right == nullptr) return {};
                    insertion = insertion->right;
                } else {
                    if (insertion->left == nullptr) return {};
                    insertion = insertion->left;
                }
            }
            if (key == insertion->key) {
                return insertion;
            }
            return {};
        }

        // start block balancing
        Node* rotateLeft(Node* node) {
            Node* p = node->right;
            node->right = p->left;
            p->left = node;
            node->updateHeight();
            p->updateHeight();
            return p;
        }

        Node* rotateRight(Node* node) {
            Node* q = node->left;
            node->left = q->right;
            q->right = node;
            node->updateHeight();
            q->updateHeight();
            return q;
        }

        Node* balancing(Node* node) {
            node->updateHeight();
            int balanceFactor = node->getBalance();
            if (balanceFactor > 1) {
                if (node->left->getBalance() < 0) {
                    node->left = rotateLeft(node->left);
                }
                node = rotateRight(node);
            } else if (balanceFactor < -1) {
                if (node->right->getBalance() > 0) {
                    node->right = rotateRight(node->right);
                }
                node = rotateLeft(node);
            }

            return node;
        }
        // end block balancing

        // start block output
        struct Trunk {
            Trunk *prev;
            std::string str;

            Trunk(Trunk *prev, std::string str) {
                this->prev = prev;
                this->str = str;
            }
        };
        void showTrunks(Trunk *p) {
            if (p == nullptr) {
                return;
            }

            showTrunks(p->prev);
            std::cout << p->str;
        }

        void printTree(Node* root, Trunk *prev, bool isLeft) {
            if (root == nullptr) {
                return;
            }

            std::string prev_str = "    ";
            Trunk *trunk = new Trunk(prev, prev_str);

            printTree(root->right, trunk, true);

            if (!prev) {
                trunk->str = "---";
            } else if (isLeft) {
                trunk->str = ".---";
                prev_str = "   |";
            } else {
                trunk->str = "`---";
                prev->str = prev_str;
            }

            showTrunks(trunk);
            std::cout << " " << root->key << std::endl;

            if (prev) {
                prev->str = prev_str;
            }
            trunk->str = "   |";

            printTree(root->left, trunk, false);
        }
        // end block output

        /// clear tree
        void free(Node* node) {
            if (!node) return;
            free(node->left);
            free(node->right);
            delete node;
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
            free(head);
            head = nullptr;
        }

        void add(const K& key, const V& value) {
            if (!head) {
                head = new Node(key, value);
                return;
            }
            insert(head, key, value);
        }

        void print() {
            printTree(head, nullptr, false);
        }

        uint32_t getSize() {
            return size;
        }

        V& operator[](const K& key) {
            std::optional<Node*> node = find(key);
            if(!node.has_value()) {
                Node* inserted = new Node(key, V());
                insert(inserted);
                return inserted->value;
            }
            return node.value()->value;
        }
    };
}

