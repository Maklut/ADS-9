// Copyright 2022 NNTU-CS
#include "tree.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

std::vector<char> generateSymbols(int n) {
    std::vector<char> symbols;
    for (int i = 0; i < n; ++i) symbols.push_back('a' + i);
    return symbols;
}

int main() {
    std::vector<char> demo = {'1', '2', '3'};
    PMTree tree(demo);
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    std::cout << "Permutations for 1,2,3:\n";
    for (size_t i = 0; i < perms.size(); ++i) {
        std::cout << i+1 << ": ";
        for (char c : perms[i]) std::cout << c;
        std::cout << "\n";
    }

    std::cout << "\ngetPerm1(2): ";
    std::vector<char> p1 = getPerm1(tree, 2);
    for (char c : p1) std::cout << c;
    std::cout << "\ngetPerm2(3): ";
    std::vector<char> p2 = getPerm2(tree, 3);
    for (char c : p2) std::cout << c;

    std::cout << "\n\nExperiment:\n";
    std::ofstream out("results.txt");
    out << "n\tgetAllPerms\tgetPerm1\tgetPerm2\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n = 3; n <= 8; ++n) {
        PMTree t(generateSymbols(n));
        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(t);
        auto end = std::chrono::high_resolution_clock::now();
        double timeAll = std::chrono::duration<double>(end - start).count();

        std::uniform_int_distribution<> dist(1, t.getTotalPermutations());
        int num = dist(gen);

        start = std::chrono::high_resolution_clock::now();
        getPerm1(t, num);
        end = std::chrono::high_resolution_clock::now();
        double time1 = std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm2(t, num);
        end = std::chrono::high_resolution_clock::now();
        double time2 = std::chrono::duration<double>(end - start).count();

        out << n << "\t" << timeAll << "\t" << time1 << "\t" << time2 << "\n";
        std::cout << "n=" << n << " done\n";
    }
    out.close();
    return 0;
}
