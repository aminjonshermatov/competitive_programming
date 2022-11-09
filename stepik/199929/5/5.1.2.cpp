//
// Created by aminjon on 11/9/22.
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
        tree[x] = __gcd(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<int> &a) {
        init((int)a.size());
        build(a, 0, 0, size);
    }

    int get_gcd(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return 0;
        if (l <= lx && rx <= r) return tree[x];

        int mid = lx + (rx - lx) / 2;
        return __gcd(get_gcd(l, r, 2 * x + 1, lx, mid), get_gcd(l, r, 2 * x + 2, mid, rx));
    }

    int get_gcd(int l, int r) {
        return get_gcd(l, r, 0, 0, size);
    }

    void update(int idx, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }

        int mid = lx + (rx - lx) / 2;
        if (idx < mid)  update(idx, v, 2 * x + 1, lx, mid);
        else            update(idx, v, 2 * x + 2, mid, rx);

        tree[x] = __gcd(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int idx, int v) {
        update(idx, v, 0, 0, size);
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
        char t;
        cin >> t;

        if (t == 's') {
            int l, r;
            cin >> l >> r;

            cout << st.get_gcd(l - 1, r) << ' ';
        } else if (t == 'u') {
            int i, x;
            cin >> i >> x;
            st.update(i - 1, x);
        }
    }
}

int main() {
    solve();
}