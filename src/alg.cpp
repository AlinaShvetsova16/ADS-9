// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>

#include "tree.h"
#include <algorithm>
#include <functional>
#include <vector>

void PMTree::buildTree(const std::vector<char>& elements) {
  if (elements.empty()) return;

  for (char elem : elements) {
    PMTree* child = new PMTree(elem);
    std::vector<char> remaining;

    for (char e : elements) {
      if (e != elem) {
        remaining.push_back(e);
      }
    }

    child->buildTree(remaining);
    children.push_back(child);
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;

  std::function<void(const PMTree*, std::vector<char>&)> dfs =
      [&](const PMTree* node, std::vector<char>& path) {
        path.push_back(node->value);

        if (node->children.empty()) {
          result.push_back(path);
        } else {
          for (const auto* child : node->children) {
            dfs(child, path);
          }
        }

        path.pop_back();
      };

  for (const auto* child : tree.children) {
    dfs(child, current);
  }

  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  auto allPerms = getAllPerms(tree);
  if (num <= 0 || num > static_cast<int>(allPerms.size())) {
    return {};
  }
  return allPerms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  int totalPerms = 1;
  int n = tree.children.size();

  for (int i = 1; i <= n; ++i) {
    totalPerms *= i;
  }

  if (num <= 0 || num > totalPerms) {
    return {};
  }

  std::vector<char> result;
  const PMTree* current = &tree;
  std::vector<char> available;

  for (const auto* child : current->children) {
    available.push_back(child->value);
  }

  int remaining = n;

  while (remaining > 0) {
    int permsPerBranch = totalPerms / remaining;
    int branchIndex = (num - 1) / permsPerBranch;

    const PMTree* nextNode = nullptr;
    int count = 0;
    for (const auto* child : current->children) {
      auto it = std::find(available.begin(), available.end(), child->value);
      if (it != available.end()) {
        if (count == branchIndex) {
          nextNode = child;
          break;
        }
        count++;
      }
    }

    if (!nextNode) return {};

    result.push_back(nextNode->value);
    available.erase(std::remove(available.begin(), available.end(),
                      nextNode->value), available.end());

    current = nextNode;
    num = ((num - 1) % permsPerBranch) + 1;
    totalPerms = permsPerBranch;
    remaining--;
  }

  return result;
}
