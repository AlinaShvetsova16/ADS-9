// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  auto perms = getAllPerms(tree);
  std::cout << "Все перестановки:\n";
  for (const auto& perm : perms) {
    for (char c : perm) {
      std::cout << c;
    }
    std::cout << "\n";
  }

  auto result1 = getPerm1(tree, 1);
  auto result2 = getPerm2(tree, 2);

  std::cout << "Перестановка 1 (метод 1): ";
  for (char c : result1) std::cout << c;
  std::cout << "\n";

  std::cout << "Перестановка 2 (метод 2): ";
  for (char c : result2) std::cout << c;
  std::cout << "\n";

  std::ofstream plotFile("result/plot.png");
  std::vector<int> sizes = {3, 4, 5, 6, 7};
  std::random_device rd;
  std::mt19937 gen(rd());

  std::cout << "\nРезультаты эксперимента:\n";
  std::cout << "n\tgetAllPerms\tgetPerm1\tgetPerm2\n";

  for (int n : sizes) {
    std::vector<char> testChars;
    for (int i = 0; i < n; ++i) {
      testChars.push_back('A' + i);
    }

    PMTree testTree(testChars);

    std::uniform_int_distribution<> dis(1, 1);
    int targetNum = dis(gen);

    auto start = std::chrono::high_resolution_clock::now();
    auto all = getAllPerms(testTree);
    auto end = std::chrono::high_resolution_clock::now();
    double timeAll = std::chrono::duration<double>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    auto p1 = getPerm1(testTree, targetNum);
    end = std::chrono::high_resolution_clock::now();
    double time1 = std::chrono::duration<double>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    auto p2 = getPerm2(testTree, targetNum);
    end = std::chrono::high_resolution_clock::now();
    double time2 = std::chrono::duration<double>(end - start).count();

    std::cout << n << "\t"
              << timeAll << "\t"
              << time1 << "\t"
              << time2 << "\n";
  }

  return 0;
}
