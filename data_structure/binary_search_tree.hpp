/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <vector>

template <typename T>
struct TreeNode {
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    T data;
};

template <typename T>
class BinarySearchTree {
 public:
    void AddNode(const T &);
    TreeNode<T> *FindNode(const T &);
    bool Has(const T &);

 private:
    TreeNode<T> *root_;
};