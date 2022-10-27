//
// Created by aminjon on 10/13/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct segtree {

    ll size;
    vector<ll> tree;

    void init(ll n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, 0);
    }

    void set(ll i, ll v, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            tree[x] += v;
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        if (i < mid) set(i, v, 2 * x + 1, lx, mid);
        else set(i, v, 2 * x + 2, mid, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void set(ll l, ll r, ll v) {
        set(l, v, 0, 0, size);
        set(r, -v, 0, 0, size);
    }

    ll sum(ll l, ll r, ll x, ll lx, ll rx) {
        if (l >= rx || r <= lx) return 0;
        if (l <= lx && rx <= r) return tree[x];

        ll mid = lx + (rx - lx) / 2;
        return sum(l, r, 2 * x + 1, lx, mid) + sum(l, r, 2 * x + 2, mid, rx);
    }

    ll sum(ll i) {
        return sum(0, i + 1, 0, 0, size);
    }

};

auto solve() {
    ll n, m;
    cin >> n >> m;

    segtree st;
    st.init(n + 1);

    for (ll k = 0; k < m; ++k) {
        ll c;
        cin >> c;

        if (c == 1) {
            ll l, r, v;
            cin >> l >> r >> v;
            st.set(l, r, v);
        } else {
            ll i;
            cin >> i;

            cout << st.sum(i) << '\n';
        }
    }
}

int32_t main() {
    solve();
}