//
// Created by aminjon on 3/12/23.
//
#include <bits/stdc++.h>

using namespace std;

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
private:
    explicit SegmentTree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
    }
public:

    template<typename U = T> explicit SegmentTree(vector<U> &A) : SegmentTree(A.size()) {
        build(A, 0, 0, size);
    }

    SegmentTree() = default;
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

    void set(int idx, T v) { modify(idx, idx, v, 0, 0, size); }
    void modify(int l, int r, T v) { modify(l, r, v, 0, 0, size); }

    Node<T> get(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return tree[x];

        auto mid = lx + (rx - lx) / 2;
        auto res = Node<T>::unite(get(l, r, 2 * x + 1, lx, mid),
                                  get(l, r, 2 * x + 2, mid, rx));
        pull(x);
        return res;
    }

    T get(int l, int r) { return get(l, r, 0, 0, size).val; }
    T get(int idx) { return get(idx, idx + 1, 0, 0, size).val; }

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

template<typename T = ::int32_t> struct Hld {
    vector<int> parent, root, depth, treePos, heavy;
    SegmentTree<T> segmentTree;

    template<typename G> explicit Hld(const G &g) {
        const int n(g.size());
        parent.assign(n, -1);
        root.assign(n, -1);
        treePos.assign(n, -1);
        heavy.assign(n, -1);
        depth.resize(n);
        depth[0] = 0;
        dfs(g, 0);

        for (int u = 0, currentPos = 0; u < n; ++u) {
            if (parent[u] == -1 || heavy[parent[u]] != u) {
                for (int v = u; ~v; v = heavy[v]) {
                    root[v] = u;
                    treePos[v] = currentPos++;
                }
            }
        }
        segmentTree.init(n);
    }

    template<typename G> int dfs(const G &g, int v) {
        int size = 1, maxSubtree = 0;
        for (auto u : g[v]) if (u != parent[v]) {
                parent[u] = v;
                depth[u] = depth[v] + 1;
                auto subtree = dfs(g, u);
                if (subtree > maxSubtree) {
                    heavy[v] = u;
                    maxSubtree = subtree;
                }
                size += subtree;
            }
        return size;
    }

    template<typename BinaryOP> void processPath(int u, int v, BinaryOP op) {
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v); // d[u] < d[v]
            op(treePos[root[v]], treePos[v] + 1);
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(treePos[u], treePos[v] + 1);
    }

    void set(int v, const T &val) {
        segmentTree.modify(treePos[v], treePos[v] + 1, v);
    }
    void modify(int u, int v, const T &val) {
        processPath(u, v, [this, &val](int l, int r) { // [l, r)
            segmentTree.modify(l, r, val);
        });
    }

    T query(int u, int v) {
        T res(0);
        processPath(u, v, [this, &res](int l, int r) { // [l, r)
            res += segmentTree.get(l, r);
        });
        return res;
    }
};
