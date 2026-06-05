// Copyright 2022 NNTU-CS
#include "tree.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

int factorial(int n) {
    int result = 1;

    for (int i = 2; i <= n; i++) {
        result *= i;
    }

    return result;
}

std::vector<std::vector<char>> getAllPerms(
    PMTree& tree) {
    std::vector<std::vector<char>> result;

    std::vector<char> current;

    tree.collect(tree.root, &current, &result);

    return result;
}

std::vector<char> getPerm1(
    PMTree& tree, int num) {
    std::vector<std::vector<char>> perms =
        getAllPerms(tree);

    if (num <= 0 ||
        num > static_cast<int>(perms.size())) {
        return {};
    }

    return perms[num - 1];
}

std::vector<char> getPerm2(
    PMTree& tree, int num) {
    std::vector<char> result;

    if (num <= 0) {
        return result;
    }

    PMTree::Node* current = tree.root;

    num--;

    while (!current->children.empty()) {
        int count =
            factorial(current->children.size() - 1);

        int index = num / count;

        if (index >=
            static_cast<int>(current->children.size())) {
            return {};
        }

        current = current->children[index];

        result.push_back(current->value);

        num %= count;
    }

    return result;
}

// Функция для генерации набора символов
std::vector<char> generateSymbols(int n) {
    std::vector<char> symbols;
    for (int i = 0; i < n; ++i) {
        symbols.push_back('a' + i);
    }
    return symbols;
}

// Функция для проведения вычислительного эксперимента
void runExperiment() {
    std::vector<int> sizes = {3, 4, 5, 6, 7, 8};
    std::ofstream resultsFile("results.txt");

    if (!resultsFile.is_open()) {
        std::cerr << "Не удалось создать файл результатов!\n";
        return;
    }

    resultsFile << "n\tgetAllPerms\tgetPerm1\tgetPerm2\n";
    std::cout << "\n=== Вычислительный эксперимент ===\n";
    std::cout << "n\tgetAllPerms(s)\tgetPerm1(s)\tgetPerm2(s)\n";
    std::cout << "----------------------------------------\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n : sizes) {
        std::vector<char> symbols = generateSymbols(n);
        PMTree tree(symbols);

        // Измеряем getAllPerms
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::vector<char>> perms = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double timeAll = std::chrono::duration<double>(end - start).count();

        // Генерируем случайный номер перестановки
        std::uniform_int_distribution<> dist(1, perms.size());
        int permNumber = dist(gen);

        // Измеряем getPerm1
        start = std::chrono::high_resolution_clock::now();
        std::vector<char> perm1 = getPerm1(tree, permNumber);
        end = std::chrono::high_resolution_clock::now();
        double time1 = std::chrono::duration<double>(end - start).count();

        // Измеряем getPerm2
        start = std::chrono::high_resolution_clock::now();
        std::vector<char> perm2 = getPerm2(tree, permNumber);
        end = std::chrono::high_resolution_clock::now();
        double time2 = std::chrono::duration<double>(end - start).count();

        resultsFile << n << "\t" << timeAll << "\t" << time1 << "\t"
                    << time2 << "\n";
        std::cout << n << "\t" << timeAll << "\t\t" << time1 << "\t\t"
                  << time2 << "\n";
    }

    resultsFile.close();
    std::cout << "\nРезультаты сохранены в файл results.txt\n";
}
