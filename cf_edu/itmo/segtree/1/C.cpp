//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1e15;

struct segtree {

    vector<ll> tree, cnt;
    int size;

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, 0);
        cnt.assign(2 * size - 1, 0);
    }

    void build(vector<ll> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) {
                tree[x] = a[lx];
                cnt[x] = 1;
            }
            return;
        }
        int mid = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
        if (tree[2 * x + 1] == tree[2 * x + 2]) cnt[x] = cnt[2 * x + 1] + cnt[2 * x + 2];
        else if (tree[2 * x + 1] < tree[2 * x + 2]) cnt[x] = cnt[2 * x + 1];
        else cnt[x] = cnt[2 * x + 2];
    }

    void build(vector<ll> &a) {
        init(a.size());
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            cnt[x] = 1;
            return;
        }
        int mid = lx + (rx - lx) / 2;
        if (i < mid)    set(i, v, 2 * x + 1, lx, mid);
        else            set(i, v, 2 * x + 2, mid, rx);
        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
        if (tree[2 * x + 1] == tree[2 * x + 2]) cnt[x] = cnt[2 * x + 1] + cnt[2 * x + 2];
        else if (tree[2 * x + 1] < tree[2 * x + 2]) cnt[x] = cnt[2 * x + 1];
        else cnt[x] = cnt[2 * x + 2];
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    pair<ll, ll> min_(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return {inf, 0};
        if (l <= lx && rx <= r) return {tree[x], cnt[x]};

        int mid = lx + (rx - lx) / 2;
        auto [mnl, cntl] = min_(l, r, 2 * x + 1, lx, mid);
        auto [mnr, cntr] = min_(l, r, 2 * x + 2, mid, rx);

        if (mnl == mnr) return {mnl, cntl + cntr};
        else if (mnl < mnr) return {mnl, cntl};
        else return {mnr, cntr};
    }

    pair<ll, ll> min_(int l, int r) {
        return min_(l, r, 0, 0, size);
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
            auto [v, cnt] = st.min_(l, r);
            cout << v << ' ' << cnt << '\n';
        }
    }
}