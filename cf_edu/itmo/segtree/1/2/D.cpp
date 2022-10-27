//
// Created by aminjon on 10/11/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct segtree {

    struct node { ll val, right; };

    ll size;
    vector<node> tree;

    node ZERO = {0, numeric_limits<ll>::max()};

    void init(ll n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, ZERO);
    }

    static node combine(node l, node r) {
        return {
            max(l.val, r.val),
            r.right
        };
    }

    void build(vector<ll> &a, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) tree[x] = {a[lx], lx};
            return;
        }

        ll m = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<ll> &a) {
        init(a.size());
        build(a, 0, 0, size);
    }

    void set(ll i, ll v, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            tree[x] = {v, i};
            return;
        }

        ll m = lx + (rx - lx) / 2;
        if (i < m) set(i, v, 2 * x + 1, lx, m);
        else set(i, v, 2 * x + 2, m, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(ll i, ll v) {
        set(i, v, 0, 0, size);
    }

    ll find_first_above(ll v, ll i, ll x, ll lx, ll rx) {
        if (tree[x].val < v || tree[x].right < i) return -1;
        if (rx - lx == 1) return lx;

        ll m = lx + (rx - lx) / 2;
        auto res = find_first_above(v, i, 2 * x + 1, lx, m);
        if (res == -1) res = find_first_above(v, i, 2 * x + 2, m, rx);
        return res;
    }

    ll find_first_above(ll v, ll i) {
        return find_first_above(v, i, 0, 0, size);
    }

};

auto solve() {
    ll n, m;
    cin >> n >> m;

    vector<ll> A(n);
    for (auto &a : A) cin >> a;

    segtree st;
    st.build(A);

    for (ll t = 0; t < m; ++t) {
        ll c;
        cin >> c;

        if (c == 1) {
            ll i, v;
            cin >> i >> v;
            st.set(i, v);
        } else if (c == 2) {
            ll v, i;
            cin >> v >> i;
            cout << st.find_first_above(v, i) << '\n';
        }
    }
}

auto main() -> int32_t {
    solve();
}