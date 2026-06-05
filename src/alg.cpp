// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <memory>
#include <vector>

PMTree::PMTree(const std::vector<char>& elements)
    : originalElements(elements), totalPermutations(0) {
    std::vector<char> sorted = elements;
    std::sort(sorted.begin(), sorted.end());

    root = std::make_shared<TreeNode>('\0');
    buildTree(root, sorted);

    totalPermutations = 1;
    for (int i = 1; i <= static_cast<int>(sorted.size()); ++i) {
        totalPermutations *= i;
    }
}

void PMTree::buildTree(std::shared_ptr<TreeNode> node,
                       std::vector<char> remaining) {
    if (remaining.empty()) {
        return;
    }

    std::sort(remaining.begin(), remaining.end());

    for (char val : remaining) {
        auto child = std::make_shared<TreeNode>(val);
        node->children.push_back(child);

        std::vector<char> newRemaining;
        for (char c : remaining) {
            if (c != val) {
                newRemaining.push_back(c);
            }
        }

        buildTree(child, newRemaining);
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    tree.getAllPermutationsRecursive(tree.root, current, result);
    return result;
}

void PMTree::getAllPermutationsRecursive(std::shared_ptr<TreeNode> node,
                                         std::vector<char>& current,
                                         std::vector<std::vector<char>>& result) {
    if (!node) return;

    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        if (!current.empty()) {
            result.push_back(current);
        }
    } else {
        for (auto& child : node->children) {
            getAllPermutationsRecursive(child, current, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<char> PMTree::getPermByTraversal(int num) {
    if (num < 1 || num > totalPermutations) {
        return std::vector<char>();
    }

    std::vector<std::vector<char>> allPerms;
    std::vector<char> current;
    getAllPermutationsRecursive(root, current, allPerms);

    if (num <= static_cast<int>(allPerms.size())) {
        return allPerms[num - 1];
    }
    return std::vector<char>();
}

std::vector<char> PMTree::getPermByNavigation(int num) {
    if (num < 1 || num > totalPermutations) {
        return std::vector<char>();
    }

    std::vector<char> result;
    std::shared_ptr<TreeNode> current = root;
    int currentTotal = totalPermutations;

    while (current && !current->children.empty()) {
        int n = static_cast<int>(current->children.size());
        int blockSize = currentTotal / n;

        int childIndex = (num - 1) / blockSize;
        num = (num - 1) % blockSize + 1;

        current = current->children[childIndex];
        result.push_back(current->value);
        currentTotal = blockSize;
    }

    return result;
}

int PMTree::countPermutationsInSubtree(std::shared_ptr<TreeNode> node,
                                       int depth,
                                       int totalDepth) {
    if (!node) return 0;
    if (depth == totalDepth) return 1;

    int count = 0;
    for (auto& child : node->children) {
        count += countPermutationsInSubtree(child, depth + 1, totalDepth);
    }
    return count;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    return tree.getPermByTraversal(num);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    return tree.getPermByNavigation(num);
}
