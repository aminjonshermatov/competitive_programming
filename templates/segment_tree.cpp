//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

using namespace std;

template<typename T = int> struct segment_tree {

    static inline constexpr T DEFAULT_VALUE = T(numeric_limits<T>::max());
    static inline constexpr T NO_OPERATION = T(-1);

    template<typename U> struct node {
        U val;
        U lazy;

        void apply([[maybe_unused]] int l, [[maybe_unused]] int r, U v) {
            val = v;
            lazy = v;
        }

        template<typename V> static node unite(const node<V> &a, const node<V> &b) {
            return node{
                    min(a.val, b.val),
                    NO_OPERATION
            };
        }
    };

    static inline constexpr node<T> NEUTRAL_ELEMENT = {DEFAULT_VALUE, NO_OPERATION};

    int size;
    vector<node<T>> tree;

    explicit segment_tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
    }

    template<typename U = T> explicit segment_tree(vector<U> &A) : segment_tree(A.size()) {
        build(A, 0, 0, size);
    }

    inline void push(int x, int lx, int rx) {
        if (rx - lx == 1 || tree[x].lazy == NO_OPERATION) return;

        int mid = lx + (rx - lx) / 2;
        tree[2 * x + 1].apply(lx, mid, tree[x].lazy);
        tree[2 * x + 2].apply(mid, rx, tree[x].lazy);
        tree[x].lazy = NO_OPERATION;
    }

    inline void pull(int x) {
        tree[x] = node<T>::unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    template<typename U = T>
    void build(vector<U> &A, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < A.size()) tree[x] = {A[lx], NO_OPERATION};
            return;
        }

        int mid = lx + (rx - lx) / 2;
        build(A, 2 * x + 1, lx, mid);
        build(A, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(int l, int r, T v, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            tree[x].apply(lx, rx, v);
            return;
        }

        int mid = lx + (rx - lx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    node<T> get(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return tree[x];

        int mid = lx + (rx - lx) / 2;
        auto res = node<T>::unite(get(l, r, 2 * x + 1, lx, mid),
                                  get(l, r, 2 * x + 2, mid, rx));
        pull(x);
        return res;
    }

    T get(int l, int r) {
        return get(l, r, 0, 0, size).val;
    }

    template<typename U>
    friend ostream& operator<<(ostream &out, const segment_tree<U> &st) {
        for (auto i = 1u, j = 0u; j < st.tree.size(); i <<= 1) {
            auto c = 0u;
            while (c++ < i) out << st.tree[j].val << ',' << st.tree[j++].lazy << ' ';
            out << '\n';
        }
        return out;
    }
};