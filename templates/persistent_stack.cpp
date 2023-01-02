//
// Created by aminjon on 1/2/23.
//
#include <bits/stdc++.h>

using namespace std;

template <typename T> struct Node {
    T val;
    uint count;
    Node *nxt;
    explicit Node(T x): val{x}, nxt{nullptr}, count{0u} { }
};

template <typename T> Node<T> *push(T num, Node<T> *node) {
    auto new_node = new Node(num);
    if (node == nullptr) {
        new_node->count = 1;
    } else {
        new_node->nxt = node;
        new_node->count = node->count + 1;
    }
    return new_node;
}

template<typename T> Node<T> *pop(Node<T> *node) {
    if (node == nullptr) return node;
    node = node->nxt;
    return node;
}

template<typename T> T peek(Node<T> *node) {
    if (node == nullptr) return -1;
    return node->val;
}