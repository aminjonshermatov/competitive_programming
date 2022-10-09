//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct segtree {

    vector<ll> tree;
    int size;

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, 0);
    }

    void build(vector<ll> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) tree[x] = a[lx];
            return;
        }
        int mid = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void build(vector<ll> &a) {
        init(a.size());
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }
        int mid = lx + (rx - lx) / 2;
        if (i < mid)    set(i, v, 2 * x + 1, lx, mid);
        else            set(i, v, 2 * x + 2, mid, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return 0;
        if (l <= lx && rx <= r) return tree[x];

        int mid = lx + (rx - lx) / 2;
        return sum(l, r, 2 * x + 1, lx, mid) + sum(l, r, 2 * x + 2, mid, rx);
    }

    ll sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

};

auto main() -> int32_t {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> A(n);
    for (auto &a : A) cin >> a;

    segtree st;
    st.build(A);

    for (int t = 0; t < m; ++t) {
        int c;
        cin >> c;

        if (c == 1) {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.sum(l, r) << '\n';
        }
    }
}