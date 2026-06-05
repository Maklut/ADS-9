// Copyright 2022 NNTU-CS
#include "tree.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

void print(std::vector<char> v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i];
    }
    std::cout << std::endl;
}

std::vector<char> generateSymbols(int n) {
    std::vector<char> symbols;
    for (int i = 0; i < n; ++i) {
        symbols.push_back('a' + i);
    }
    return symbols;
}

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
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::vector<char>> perms = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double timeAll = std::chrono::duration<double>(end - start).count();
        std::uniform_int_distribution<> dist(1, perms.size());
        int permNumber = dist(gen);
        start = std::chrono::high_resolution_clock::now();
        std::vector<char> perm1 = getPerm1(tree, permNumber);
        end = std::chrono::high_resolution_clock::now();
        double time1 = std::chrono::duration<double>(end - start).count();
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

int main() {
    std::vector<char> in = {'1', '3', '5', '7'};
    PMTree tree(in);
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    std::cout << "Все перестановки для {1,3,5,7}:\n";
    for (size_t i = 0; i < perms.size(); i++) {
        std::cout << i + 1 << ": ";
        print(perms[i]);
    }
    std::cout << "\nПроверка getPerm1(1): ";
    print(getPerm1(tree, 1));
    std::cout << "Проверка getPerm2(2): ";
    print(getPerm2(tree, 2));
    runExperiment();
    return 0;
}
