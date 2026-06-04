// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
public:
    char value;
    std::vector<PMTree*> children;

    PMTree() : value('\0') {}

    PMTree(char val) : value(val) {}

    ~PMTree() {
        for (auto* child : children) {
            delete child;
        }
    }

    void buildTree(const std::vector<char>& elements);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif // INCLUDE_TREE_H_
