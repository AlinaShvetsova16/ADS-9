// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char v) : value(v) {}
    ~Node() {
        for (auto child : children) delete child;
    }
};

class PMTree {
 public:
    Node* root;
    explicit PMTree(std::vector<char> chars);
    ~PMTree() { if (root) delete root; }
 private:
    void buildTree(Node* node, std::vector<char> remaining);
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
