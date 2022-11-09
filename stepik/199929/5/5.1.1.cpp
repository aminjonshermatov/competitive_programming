//
// Created by aminjon on 11/9/22.
//
#include <bits/stdc++.h>

using namespace std;

inline constexpr int n_inf = numeric_limits<int>::min();

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, n_inf);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) tree[x] = a[lx];
            return;
        }

        int mid = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<int> &a) {
        init(a.size());
        build(a, 0, 0, size);
    }

    int get_max(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return n_inf;
        if (l <= lx && rx <= r) return tree[x];

        int mid = lx + (rx - lx) / 2;
        return max(get_max(l, r, 2 * x + 1, lx, mid), get_max(l, r, 2 * x + 2, mid, rx));
    }

    int get_max(int l, int r) {
        return get_max(l, r, 0, 0, size);
    }

};

auto solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &a : A) cin >> a;

    segtree st;
    st.build(A);

    int M;
    cin >> M;
    for (int _ = 0; _ < M; ++_) {
        int l, r;
        cin >> l >> r;
        cout << st.get_max(l - 1, r) << ' ';
    }
}

int main() {
    solve();
}