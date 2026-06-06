// Copyright 2022 NNTU-CS
#include "tree.h"
#include <vector>
#include <cstdint>

PMTree::PMTree(std::vector<char> chars) {
    root = nullptr;
    if (chars.empty()) return;
    root = new Node(0);
    buildTree(root, chars);
}

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;
    for (size_t i = 0; i < remaining.size(); ++i) {
        Node* child = new Node(remaining[i]);
        node->children.push_back(child);
        std::vector<char> next;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (j != i) next.push_back(remaining[j]);
        }
        buildTree(child, next);
    }
}

static void dfsCollect(Node* node, std::vector<char>& path,
                       std::vector<std::vector<char>>& result) {
    if (!node) return;
    if (node->value != 0) path.push_back(node->value);
    if (node->children.empty()) {
        result.push_back(path);
    } else {
        for (auto child : node->children) {
            dfsCollect(child, path, result);
        }
    }
    if (node->value != 0) path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    if (!tree.root) return result;
    std::vector<char> path;
    dfsCollect(tree.root, path, result);
    return result;
}

static void dfsNum(Node* node, std::vector<char>& path, int& count,
                   int target, std::vector<char>& out) {
    if (!node || !out.empty()) return;
    if (node->value != 0) path.push_back(node->value);
    if (node->children.empty()) {
        ++count;
        if (count == target) out = path;
    } else {
        for (auto child : node->children) {
            dfsNum(child, path, count, target, out);
        }
    }
    if (node->value != 0) path.pop_back();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<char> out;
    if (!tree.root || num <= 0) return out;
    int count = 0;
    std::vector<char> path;
    dfsNum(tree.root, path, count, num, out);
    return out;
}

static int64_t factorial(int n) {
    int64_t f = 1;
    for (int i = 2; i <= n; ++i) f *= i;
    return f;
}

static void navigatePerm(Node* node, std::vector<char>& path,
                         int num, std::vector<char>& out) {
    if (!node || !out.empty()) return;
    if (node->value != 0) path.push_back(node->value);
    if (node->children.empty()) {
        if (num == 1) out = path;
        return;
    }
    int k = static_cast<int>(node->children.size());
    int64_t block = factorial(k - 1);
    int idx = static_cast<int>((num - 1) / block);
    if (idx >= k) return;
    int nextNum = num - idx * static_cast<int>(block);
    navigatePerm(node->children[idx], path, nextNum, out);
    if (node->value != 0) path.pop_back();
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> out;
    if (!tree.root || num <= 0) return out;
    std::vector<char> path;
    navigatePerm(tree.root, path, num, out);
    return out;
}
