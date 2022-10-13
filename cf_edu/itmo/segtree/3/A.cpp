//
// Created by aminjon on 10/13/22.
//
#include <bits/stdc++.h>

using namespace std;

struct segtree {

    int size;
    vector<int> tree;

    void init(size_t n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, 0);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }

        int mid = lx + (rx - lx) / 2;
        if (i < mid) set(i, v, 2 * x + 1, lx, mid);
        else set(i, v, 2 * x + 2, mid, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
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
        return sum(l, r, 0, 0, size);
    }

};

auto solve() {
    int n;
    cin >> n;

    segtree st;
    st.init(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        auto s = st.sum(x, n + 1);
        st.set(x - 1, 1);
        cout << s << ' ';
    }
    cout << '\n';
}

int32_t main() {
    solve();
}