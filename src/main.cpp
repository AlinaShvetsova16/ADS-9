// Copyright 2022 NNTU-CS
#include <cstdlib>
#include <fstream>
#include <locale>
#include <iostream>
#include <vector>
#include "tree.h"

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);
    std::vector<std::vector<char>> perms = getPermAll(tree);
    for (const auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << '\n';
    }
    std::vector<char> r1 = getPerm1(tree, 1);
    std::vector<char> r2 = getPerm2(tree, 2);
    return 0;
}
