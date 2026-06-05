// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 private:
    struct Node {
        char value;
        std::vector<Node*> children;
        explicit Node(char val) {
            value = val;
        }
    };

    Node* root;

    void build(Node* node, std::vector<char> elems) {
        if (elems.empty()) {
            return;
        }

        for (size_t i = 0; i < elems.size(); i++) {
            Node* child = new Node(elems[i]);

            node->children.push_back(child);

            std::vector<char> rest;

            for (size_t j = 0; j < elems.size(); j++) {
                if (i != j) {
                    rest.push_back(elems[j]);
                }
            }

            build(child, rest);
        }
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        for (size_t i = 0; i < node->children.size(); i++) {
            clear(node->children[i]);
        }

        delete node;
    }

    void collect(Node* node,
        std::vector<char>* current,
        std::vector<std::vector<char>>* result) const {
        if (node->children.empty()) {
            result->push_back(*current);

            return;
        }

        for (size_t i = 0; i < node->children.size(); i++) {
            current->push_back(node->children[i]->value);

            collect(node->children[i], current, result);

            current->pop_back();
        }
    }

    friend std::vector<std::vector<char>> getAllPerms(
        PMTree& tree);

    friend std::vector<char> getPerm1(
        PMTree& tree, int num);

    friend std::vector<char> getPerm2(
        PMTree& tree, int num);

 public:
    explicit PMTree(std::vector<char> elems) {
        root = new Node('*');

        build(root, elems);
    }

    ~PMTree() {
        clear(root);
    }
};

std::vector<std::vector<char>> getAllPerms(
    PMTree& tree);

std::vector<char> getPerm1(
    PMTree& tree, int num);

std::vector<char> getPerm2(
    PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
