//
// Created by aminjon on 10/13/22.
//
#include <bits/stdc++.h>

using namespace std;

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, 0);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) tree[x] = a[lx];
            return;
        }

        int mid = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void build(vector<int> &a) {
        init((int)a.size());
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }

        int mid = lx + (rx - lx) / 2;
        if (i < mid) set(i, v, 2 * x + 1, lx, mid);
        else set(i, v, 2 * x + 2, mid, rx);
        tree[x] =  tree[2 * x + 1] + tree[2 * x + 2];
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return 0;
        if (l <= lx && rx <= r) return tree[x];

        int mid = lx + (rx - lx) / 2;
        return sum(l, r, 2 * x + 1, lx, mid) + sum(l, r, 2 * x + 2, mid, rx);
    }

    int sum(int l, int r) {
        return sum(l, r, 0, 0, size);;
    }

};

auto solve() {
    int n;
    cin >> n;
    vector<int> E(n), O(n);
    for (auto &e : E) cin >> e;

    for (int i = 1; i < n; i += 2) {
        O[i] = E[i];
        E[i] = 0;
    }

    segtree st_e, st_o;
    st_e.build(E);
    st_o.build(O);

    int m;
    cin >> m;
    for (int t = 0; t < m; ++t) {
        int c;
        cin >> c;

        if (c == 0) {
            int i, v;
            cin >> i >> v;

            --i;
            if (i & 1) st_o.set(i, v);
            else st_e.set(i, v);
        } else if (c == 1) {
            int l, r;
            cin >> l >> r;

            --l;
            auto e = st_e.sum(l, r);
            auto o = st_o.sum(l, r);
            cout << (l & 1 ? o - e : e - o) << '\n';
        }
    }
}

int32_t main() {
    solve();
}