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
        init(a.size());
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
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int get_kth(int k, int x, int lx, int rx) {
        if (rx - lx == 1 || tree[x] == k) return lx;

        int mid = lx + (rx - lx) / 2;
        if (tree[2 * x + 2] > k) return get_kth(k, 2 * x + 2, mid, rx);
        return get_kth(k - tree[2 * x + 2], 2 * x + 1, lx, mid);
    }

    int get_kth(int k) {
        return get_kth(k, 0, 0, size);
    }

};

auto solve() {
    int n;
    cin >> n;

    vector<int> a(n, 1);

    segtree st;
    st.build(a);

    vector<int> p(n), res(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    for (int i = n - 1; i >= 0; --i) {
        res[i] = st.get_kth(p[i]);
        st.set(res[i], 0);
    }

    for (auto el : res) cout << el + 1 << ' ';
    cout << '\n';
}

int main() {
    solve();
}