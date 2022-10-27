//
// Created by aminjon on 10/11/22.
//
#include <bits/stdc++.h>

using namespace std;

struct segtree {

    vector<int> tree;
    int size;

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

        int m = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void build(vector<int> &a) {
        init(a.size());
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }

        int m = lx + (rx - lx) / 2;
        if (i < m) set(i, v, 2 * x + 1, lx, m);
        else set(i, v, 2 * x + 2, m, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void set(int i, int x) {
        set(i, x, 0, 0, size);
    }

    int find_kth(int k, int x, int lx, int rx) {
        if (rx - lx == 1) return lx;
        if (tree[x] == k) return rx;

        int m = lx + (rx - lx) / 2;
        if (tree[2 * x + 1] > k) return find_kth(k, 2 * x + 1, lx, m);
        return find_kth(k - tree[2 * x + 1], 2 * x + 2, m, rx);
    }

    int find_kth(int k) {
        return find_kth(k, 0, 0, size);
    }

};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> A(n);
    for (int i = 0; i < n; ++i) cin >> A[i];

    segtree st;
    st.build(A);

    for (int t = 0; t < m; ++t) {
        int c;
        cin >> c;
        if (c == 1) {
            int i;
            cin >> i;

            st.set(i, A[i] = 1 - A[i]);
        } else if (c == 2) {
            int k;
            cin >> k;
            cout << st.find_kth(k) << '\n';
        }
    }
}

auto main() -> int32_t {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
}