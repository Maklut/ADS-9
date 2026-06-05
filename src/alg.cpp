// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <cmath>

// Конструктор дерева
PMTree::PMTree(const std::vector<char>& elements) 
    : originalElements(elements), totalPermutations(0) {
    // Сортируем элементы для правильного порядка
    std::vector<char> sorted = elements;
    std::sort(sorted.begin(), sorted.end());
    
    // Создаем корень с пустым значением
    root = std::make_shared<TreeNode>('\0');
    
    // Строим дерево
    buildTree(root, sorted);
    
    // Вычисляем общее количество перестановок
    totalPermutations = 1;
    for (int i = 1; i <= static_cast<int>(sorted.size()); ++i) {
        totalPermutations *= i;
    }
}

// Рекурсивное построение дерева
void PMTree::buildTree(std::shared_ptr<TreeNode> node, std::vector<char> remaining) {
    if (remaining.empty()) {
        return;
    }
    
    // Сортируем оставшиеся элементы для правильного порядка
    std::sort(remaining.begin(), remaining.end());
    
    // Для каждого оставшегося элемента создаем потомка
    for (char val : remaining) {
        auto child = std::make_shared<TreeNode>(val);
        node->children.push_back(child);
        
        // Создаем вектор оставшихся элементов (без текущего)
        std::vector<char> newRemaining;
        for (char c : remaining) {
            if (c != val) {
                newRemaining.push_back(c);
            }
        }
        
        // Рекурсивно строим поддерево
        buildTree(child, newRemaining);
    }
}

// Получение всех перестановок
std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    tree.getAllPermutationsRecursive(tree.root, current, result);
    return result;
}

// Рекурсивный обход для получения всех перестановок
void PMTree::getAllPermutationsRecursive(std::shared_ptr<TreeNode> node, 
                                         std::vector<char>& current, 
                                         std::vector<std::vector<char>>& result) {
    if (!node) return;
    
    // Пропускаем корневой узел (он пустой)
    if (node->value != '\0') {
        current.push_back(node->value);
    }
    
    // Если достигли листа (нет детей), сохраняем перестановку
    if (node->children.empty()) {
        if (!current.empty()) {
            result.push_back(current);
        }
    } else {
        // Рекурсивно обходим всех детей
        for (auto& child : node->children) {
            getAllPermutationsRecursive(child, current, result);
        }
    }
    
    // Возвращаемся назад
    if (node->value != '\0') {
        current.pop_back();
    }
}

// Получение перестановки по номеру (способ 1: полный обход)
std::vector<char> PMTree::getPermByTraversal(int num) {
    // Проверяем существование перестановки
    if (num < 1 || num > totalPermutations) {
        return std::vector<char>();
    }
    
    // Получаем все перестановки и берем нужную
    std::vector<std::vector<char>> allPerms;
    std::vector<char> current;
    getAllPermutationsRecursive(root, current, allPerms);
    
    if (num <= static_cast<int>(allPerms.size())) {
        return allPerms[num - 1];
    }
    return std::vector<char>();
}

// Получение перестановки по номеру (способ 2: навигация по дереву)
std::vector<char> PMTree::getPermByNavigation(int num) {
    // Проверяем существование перестановки
    if (num < 1 || num > totalPermutations) {
        return std::vector<char>();
    }
    
    std::vector<char> result;
    std::shared_ptr<TreeNode> current = root;
    
    while (current && !current->children.empty()) {
        int n = static_cast<int>(current->children.size());
        int blockSize = totalPermutations / n;
        
        // Определяем, какой ребенок содержит нужную перестановку
        int childIndex = (num - 1) / blockSize;
        
        // Обновляем номер для следующего уровня
        num = (num - 1) % blockSize + 1;
        
        // Переходим к выбранному ребенку
        current = current->children[childIndex];
        result.push_back(current->value);
        
        // Обновляем totalPermutations для следующего уровня
        if (current->children.empty()) {
            break;
        }
        totalPermutations = blockSize;
    }
    
    // Восстанавливаем исходное значение totalPermutations
    totalPermutations = 1;
    for (int i = 1; i <= static_cast<int>(originalElements.size()); ++i) {
        totalPermutations *= i;
    }
    
    return result;
}

// Внешние функции-обертки
std::vector<char> getPerm1(PMTree& tree, int num) {
    return tree.getPermByTraversal(num);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    return tree.getPermByNavigation(num);
}
