//
// Created by aminjon on 10/27/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

inline constexpr auto inf = numeric_limits<ll>::max();

struct segtree {

    ll size;
    vector<ll> tree;

    explicit segtree(ll n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, 0);
    }

    void propagate(ll x, ll lx, ll rx) {
        if (tree[x] == inf || rx - lx == 1) return;

        tree[2 * x + 1] = tree[x];
        tree[2 * x + 2] = tree[x];
        tree[x] = inf;
    }

    void range_set(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        propagate(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            tree[x] = v;
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        range_set(l, r, v, 2 * x + 1, lx, mid);
        range_set(l, r, v, 2 * x + 2, mid, rx);
    }

    void range_set(ll l, ll r, ll v) {
        range_set(l, r, v, 0, 0, size);
    }

    ll get(ll i, ll x, ll lx, ll rx) {
        propagate(x, lx, rx);
        if (rx - lx == 1) return tree[x];

        ll mid = lx + (rx - lx) / 2;
        if (i < mid) return get(i, 2 * x + 1, lx, mid);
        else return get(i, 2 * x + 2, mid, rx);
    }

    ll get(ll i) {
        return get(i, 0, 0, size);
    }

};

void solve() {
    ll n, m;
    cin >> n >> m;

    segtree st(n);
    for (ll q = 0; q < m; ++q) {
        char c;
        cin >> c;

        if (c == '1') {
            ll l, r, v;
            cin >> l >> r >> v;

            st.range_set(l, r, v);
        } else if (c == '2') {
            ll i;
            cin >> i;

            cout << st.get(i) << '\n';
        }
    }
}

int main() {
    solve();
}