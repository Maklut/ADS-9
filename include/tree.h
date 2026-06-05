// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <memory>
#include <vector>

// Узел дерева
struct TreeNode {
    char value;
    std::vector<std::shared_ptr<TreeNode>> children;

    explicit TreeNode(char val) : value(val) {}
};

// Класс дерева перестановок
class PMTree {
 public:
    explicit PMTree(const std::vector<char>& elements);
    ~PMTree() = default;

    std::shared_ptr<TreeNode> getRoot() const { return root; }
    int getTotalPermutations() const { return totalPermutations; }
    const std::vector<char>& getOriginalElements() const {
        return originalElements;
    }

    // Дружественные функции
    friend std::vector<std::vector<char>> getAllPerms(PMTree& tree);
    friend std::vector<char> getPerm1(PMTree& tree, int num);
    friend std::vector<char> getPerm2(PMTree& tree, int num);

 private:
    std::shared_ptr<TreeNode> root;
    std::vector<char> originalElements;
    int totalPermutations;

    void buildTree(std::shared_ptr<TreeNode> node,
                   std::vector<char> remaining);
    void getAllPermutationsRecursive(std::shared_ptr<TreeNode> node,
                                     std::vector<char>& current,
                                     std::vector<std::vector<char>>& result);
    std::vector<char> getPermByTraversal(int num);
    std::vector<char> getPermByNavigation(int num);
    int countPermutationsInSubtree(std::shared_ptr<TreeNode> node,
                                   int depth,
                                   int totalDepth);
};

// Функции для работы с деревом
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
