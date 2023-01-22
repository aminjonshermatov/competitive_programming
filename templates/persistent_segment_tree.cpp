//
// Created by aminjon on 1/22/23.
//
#include <bits/stdc++.h>

using namespace std;

namespace persistent_segment_tree {
    template<typename T> struct Node {
        T val;
        Node *left, *right;

        Node() : Node(-1) { }
        explicit Node(T val_, Node<T> *left_ = nullptr, Node<T> *right_ = nullptr) : val(val_), left(left_), right(right_) { }
    };

    template <typename T> Node<T> EMPTY_NODE = Node<T>(T(0));

    template <typename T> inline Node<T>* get_node(Node<T> *node) { return node == nullptr ? &EMPTY_NODE<T> : node; }
    template <typename T> inline Node<T>* unite(Node<T> *left, Node<T> *right) { return new Node<T>(left->val + right->val, left, right); }


    template<typename T> Node<T>* build(vector<T> &A, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < A.size()) return new Node<T>(A[lx]);
            return nullptr;
        }

        auto mid = lx + (rx - lx) / 2;
        return unite(get_node(build(A, lx, mid)), get_node(build(A, mid, rx)));
    }

    template<typename T> Node<T>* modify(int idx, T new_v, Node<T> *cur, int lx, int rx) {
        if (rx - lx == 1) return new Node<T>(new_v + get_node(cur)->val);

        auto mid = lx + (rx - lx) / 2;
        Node<T> new_node = Node<T>();
        assert(cur != nullptr);
        if (idx < mid)  new_node.left =  modify(idx, new_v, cur->left, lx, mid), new_node.right = cur->right;
        else            new_node.right = modify(idx, new_v, cur->right, mid, rx), new_node.left = cur->left;
        return unite(get_node(new_node.left), get_node(new_node.right));
    }

    template<typename T> Node<T>* get(int l, int r, Node<T> *cur, int lx, int rx) {
        if (l >= rx || r <= lx) return nullptr;
        if (l <= lx && rx <= r) return cur;

        auto mid = lx + (rx - lx) / 2;
        assert(cur != nullptr);
        return unite(get_node(get(l, r, cur->left, lx, mid)), get_node(get(l, r, cur->right, mid, rx)));
    }

    template<typename T> T get_safe(int l, int r, Node<T> *cur, int lx, int rx) {
        return get_node(get(l, r, cur, lx, rx))->val;
    }

};
using namespace persistent_segment_tree;