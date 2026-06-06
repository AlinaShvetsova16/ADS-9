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

class Tree {
 public:
    Node* root;
    explicit Tree(std::vector<char> chars);
    ~Tree() { if (root) delete root; }
 private:
    void buildTree(Node* node, std::vector<char> remaining);
};

std::vector<std::vector<char>> getAllPerms(Tree& tree);
std::vector<char> getPerm1(Tree& tree, int num);
std::vector<char> getPerm2(Tree& tree, int num);

#endif  // INCLUDE_TREE_H_
