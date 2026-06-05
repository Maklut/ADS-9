// Copyright 2022 NNTU-CS
#include "tree.h"
#include <vector>

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    tree.collect(tree.root, &current, &result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    if (num <= 0 || num > static_cast<int>(perms.size())) {
        return {};
    }
    return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result;
    if (num <= 0) {
        return result;
    }
    PMTree::Node* current = tree.root;
    num--;
    while (!current->children.empty()) {
        int count = factorial(current->children.size() - 1);
        int index = num / count;
        if (index >= static_cast<int>(current->children.size())) {
            return {};
        }
        current = current->children[index];
        result.push_back(current->value);
        num %= count;
    }
    return result;
}
