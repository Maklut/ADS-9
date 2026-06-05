// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>

#include "tree.h"

void print(std::vector<char> v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i];
    }
    std::cout << std::endl;
}

// Объявляем функцию эксперимента
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

    // Запускаем вычислительный эксперимент
    runExperiment();

    return 0;
}
