//
// Created by aminjon on 10/27/22.
//
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct segtree {

    ll size;
    vector<ll> tree;

    explicit segtree(ll n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, 0);
    }

    void range_max(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            tree[x] = max(tree[x], v);
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        range_max(l, r, v, 2 * x + 1, lx, mid);
        range_max(l, r, v, 2 * x + 2, mid, rx);
    }

    // [l, r): A[i] = max(A[i], v)
    void range_max(ll l, ll r, ll v) {
        range_max(l, r, v, 0, 0, size);
    }

    ll get(ll i, ll x, ll lx, ll rx) {
        if (rx - lx == 1) return tree[x];

        ll mid = lx + (rx - lx) / 2;
        if (i < mid) return max(get(i, 2 * x + 1, lx, mid), tree[x]);
        else return max(get(i, 2 * x + 2, mid, rx), tree[x]);
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
            st.range_max(l, r, v);
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