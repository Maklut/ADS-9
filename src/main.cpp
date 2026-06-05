// Copyright 2022 NNTU-CS
#include "tree.h"

#include <iostream>
#include <vector>

void print(std::vector<char> v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i];
    }
    std::cout << std::endl;
}

void runExperiment();

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
