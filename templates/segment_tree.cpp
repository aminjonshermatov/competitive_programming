//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

using namespace std;

auto GE =   []<typename T>(const T &tree_val, const T &given) -> T { return tree_val >= given; };
auto G =    []<typename T>(const T &tree_val, const T &given) -> T { return tree_val > given; };
auto LE =   []<typename T>(const T &tree_val, const T &given) -> T { return tree_val <= given; };
auto L =    []<typename T>(const T &tree_val, const T &given) -> T { return tree_val < given; };

template<typename T = int> struct SegmentTree {

    static inline constexpr T DEFAULT_VALUE = T(0);
    static inline constexpr T DEFAULT_LAZY = T(0);

    template<typename U> struct Node {
        U val;
        U lazy;
        int right;
        bool has_lazy;

        void apply([[maybe_unused]] int l, [[maybe_unused]] int r, U v) {
            val += v;
            lazy += v;
            has_lazy = true;
        }

        template<typename V> static Node unite(const Node<V> &a, const Node<V> &b) {
            return Node{
                    a.val + b.val,
                    DEFAULT_LAZY,
                    b.right,
                    false
            };
        }
    };

    static inline constexpr Node<T> NEUTRAL_ELEMENT = {DEFAULT_VALUE, DEFAULT_LAZY, -1, false};

    int size;
    vector<Node<T>> tree;

    SegmentTree() = default;
    explicit SegmentTree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
        build(0, 0, size);
    }
    template<typename U = T> explicit SegmentTree(vector<U> &A) : SegmentTree(A.size()) {
        size = 1;
        while (size < A.size()) size <<= 1;
        tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
        build(A, 0, 0, size);
    }

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.resize(2 * size - 1);
        build(0, 0, size);
    }

    inline void push(int x, int lx, int rx) {
        if (rx - lx == 1 || !tree[x].has_lazy) return;

        auto mid = lx + (rx - lx) / 2;
        tree[2 * x + 1].apply(lx, mid, tree[x].lazy);
        tree[2 * x + 2].apply(mid, rx, tree[x].lazy);
        tree[x].lazy = DEFAULT_LAZY;
        tree[x].has_lazy = false;
    }

    inline void pull(int x) {
        tree[x] = Node<T>::unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = {DEFAULT_VALUE, DEFAULT_LAZY, lx, false};
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        build(2 * x + 1, lx, mid);
        build(2 * x + 2, mid, rx);
        pull(x);
    }

    template<typename U = T>
    void build(vector<U> &A, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < A.size()) tree[x] = {A[lx], DEFAULT_LAZY, lx, false};
            return;
        }

        auto mid = lx + (rx - lx) / 2;
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

        auto mid = lx + (rx - lx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(int idx, T v) { modify(idx, idx, v, 0, 0, size); }
    void modify(int l, int r, T v) { modify(l, r, v, 0, 0, size); }

    Node<T> query(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return tree[x];

        auto mid = lx + (rx - lx) / 2;
        auto res = Node<T>::unite(query(l, r, 2 * x + 1, lx, mid),
                                  query(l, r, 2 * x + 2, mid, rx));
        pull(x);
        return res;
    }

    T query(int l, int r) { return query(l, r, 0, 0, size).val; }
    T query(int idx) { return query(idx, idx + 1, 0, 0, size).val; }

    template<typename Op> T get_first(T v, int i, int x, int lx, int rx, Op &op) {
        if (!op(tree[x].val, v) || tree[x].right < i) return -1;
        if (rx - lx == 1) return lx;

        auto mid = lx + (rx - lx) / 2;
        auto res = get_first(v, i, 2 * x + 1, lx, mid, op);
        if (res == -1) res = get_first(v, i, 2 * x + 2, mid, rx, op);
        return res;
    }

    template<typename Op> T get_first(T v, int i, Op &op) {
        return get_first(v, i, 0, 0, size, op);
    }

    template<typename U>
    friend ostream& operator<<(ostream &out, const SegmentTree<U> &st) {
        for (auto i = 1u, j = 0u; j < st.tree.size(); i <<= 1) {
            auto c = 0u;
            while (c++ < i) out << st.tree[j].val << ',' << st.tree[j++].lazy << ' ';
            out << '\n';
        }
        return out;
    }
};

struct SegmentTree {
    int n;
    vector<int> tree;

    static inline constexpr auto neutral = numeric_limits<int>::min();

    explicit SegmentTree(int n_) : n(n_), tree(2 * n_, neutral) { }

    void set(int pos, int nval) {
        pos += n;
        tree[pos] = nval;
        while (pos > 1) {
            pos >>= 1;
            tree[pos] = max(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }

    int query(int ql, int qr) {
        ql += n; qr += n;
        auto ans = ninf;
        while (ql < qr) {
            if (ql & 1) ans = max(ans, tree[ql++]);
            if (qr & 1) ans = max(ans, tree[--qr]);
            ql >>= 1;
            qr >>= 1;
        }
        return ans;
    }

};