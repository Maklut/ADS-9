// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>
#include <algorithm>

// Узел дерева
struct TreeNode {
    char value;
    std::vector<std::shared_ptr<TreeNode>> children;
    
    TreeNode(char val) : value(val) {}
};

// Класс дерева перестановок
class PMTree {
private:
    std::shared_ptr<TreeNode> root;
    std::vector<char> originalElements;
    int totalPermutations;
    
    // Рекурсивное построение дерева
    void buildTree(std::shared_ptr<TreeNode> node, std::vector<char> remaining);
    
    // Рекурсивный обход для получения всех перестановок
    void getAllPermutationsRecursive(std::shared_ptr<TreeNode> node, 
                                     std::vector<char>& current, 
                                     std::vector<std::vector<char>>& result);
    
    // Получение перестановки по номеру (способ 1: полный обход)
    std::vector<char> getPermByTraversal(int num);
    
    // Получение перестановки по номеру (способ 2: навигация по дереву)
    std::vector<char> getPermByNavigation(int num);
    
    // Подсчет количества перестановок в поддереве
    int countPermutationsInSubtree(std::shared_ptr<TreeNode> node, int depth, int totalDepth);
    
public:
    // Конструктор
    PMTree(const std::vector<char>& elements);
    
    // Деструктор
    ~PMTree() = default;
    
    // Дружественные функции
    friend std::vector<std::vector<char>> getAllPerms(PMTree& tree);
    friend std::vector<char> getPerm1(PMTree& tree, int num);
    friend std::vector<char> getPerm2(PMTree& tree, int num);
    
    // Геттеры
    std::shared_ptr<TreeNode> getRoot() const { return root; }
    int getTotalPermutations() const { return totalPermutations; }
    const std::vector<char>& getOriginalElements() const { return originalElements; }
};

// Функции для работы с деревом
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
