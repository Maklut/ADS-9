// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <iomanip>
#include "tree.h"

// Функция для генерации набора символов заданного размера
std::vector<char> generateSymbols(int n) {
    std::vector<char> symbols;
    for (int i = 0; i < n; ++i) {
        symbols.push_back('a' + i);
    }
    return symbols;
}

// Функция для измерения времени выполнения getAllPerms
double measureGetAllPerms(PMTree& tree) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Функция для измерения времени выполнения getPerm1
double measureGetPerm1(PMTree& tree, int permNumber) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<char> perm = getPerm1(tree, permNumber);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Функция для измерения времени выполнения getPerm2
double measureGetPerm2(PMTree& tree, int permNumber) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<char> perm = getPerm2(tree, permNumber);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    std::cout << "=== Демонстрация работы с деревом перестановок ===\n\n";
    
    // Демонстрация для '1','2','3'
    std::vector<char> demoElements = {'1', '2', '3'};
    PMTree demoTree(demoElements);
    
    std::cout << "Исходные элементы: ";
    for (char c : demoElements) std::cout << c << " ";
    std::cout << "\n\n";
    
    // Получение всех перестановок
    std::cout << "Все перестановки:\n";
    std::vector<std::vector<char>> allPerms = getAllPerms(demoTree);
    for (size_t i = 0; i < allPerms.size(); ++i) {
        std::cout << i + 1 << ": ";
        for (char c : allPerms[i]) std::cout << c;
        std::cout << "\n";
    }
    
    // Демонстрация getPerm1
    std::cout << "\n=== Демонстрация getPerm1 ===\n";
    for (int i = 1; i <= 6; ++i) {
        std::vector<char> perm = getPerm1(demoTree, i);
        std::cout << "getPerm1(" << i << ") = ";
        if (!perm.empty()) {
            for (char c : perm) std::cout << c;
            std::cout << "\n";
        } else {
            std::cout << "(не существует)\n";
        }
    }
    
    // Демонстрация getPerm2
    std::cout << "\n=== Демонстрация getPerm2 ===\n";
    for (int i = 1; i <= 6; ++i) {
        std::vector<char> perm = getPerm2(demoTree, i);
        std::cout << "getPerm2(" << i << ") = ";
        if (!perm.empty()) {
            for (char c : perm) std::cout << c;
            std::cout << "\n";
        } else {
            std::cout << "(не существует)\n";
        }
    }
    
    // Проверка несуществующей перестановки
    std::cout << "\nПроверка несуществующей перестановки:\n";
    std::vector<char> invalidPerm = getPerm1(demoTree, 10);
    std::cout << "getPerm1(10) = " << (invalidPerm.empty() ? "(пустой вектор)" : "не пустой") << "\n";
    
    std::cout << "\n=== Вычислительный эксперимент ===\n";
    
    // Размеры алфавита для тестирования
    std::vector<int> sizes = {3, 4, 5, 6, 7, 8, 9, 10};
    
    // Открываем файл для записи результатов
    std::ofstream resultsFile("results.txt");
    if (!resultsFile.is_open()) {
        std::cerr << "Не удалось создать файл результатов!\n";
        return 1;
    }
    
    resultsFile << "n\tgetAllPerms\tgetPerm1\tgetPerm2\n";
    std::cout << std::setw(4) << "n" 
              << std::setw(15) << "getAllPerms(s)" 
              << std::setw(15) << "getPerm1(s)" 
              << std::setw(15) << "getPerm2(s)\n";
    std::cout << std::string(50, '-') << "\n";
    
    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int n : sizes) {
        std::cout << "Тестирование для n = " << n << "... ";
        std::cout.flush();
        
        // Генерируем символы
        std::vector<char> symbols = generateSymbols(n);
        
        // Создаем дерево
        PMTree tree(symbols);
        
        // Измеряем время getAllPerms
        double timeAll = measureGetAllPerms(tree);
        
        // Генерируем случайные номера перестановок
        std::uniform_int_distribution<> dist(1, tree.getTotalPermutations());
        int permNumber = dist(gen);
        
        // Измеряем время getPerm1
        double time1 = measureGetPerm1(tree, permNumber);
        
        // Измеряем время getPerm2
        double time2 = measureGetPerm2(tree, permNumber);
        
        // Записываем результаты
        resultsFile << n << "\t" << timeAll << "\t" << time1 << "\t" << time2 << "\n";
        
        // Выводим на экран
        std::cout << "готово\n";
        std::cout << std::setw(4) << n 
                  << std::setw(15) << std::fixed << std::setprecision(6) << timeAll
                  << std::setw(15) << time1
                  << std::setw(15) << time2 << "\n";
    }
    
    resultsFile.close();
    std::cout << "\nРезультаты сохранены в файл results.txt\n";
    std::cout << "Для построения графика запустите plot.py\n";
    
    return 0;
}
