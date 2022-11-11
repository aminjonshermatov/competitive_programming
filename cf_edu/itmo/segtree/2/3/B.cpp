//
// Created by aminjon on 11/10/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct segtree {

    static inline constexpr ll DEFAULT_VALUE = 0ll;
    static inline constexpr ll NO_OPERATION = 0ll;

    struct node {
        ll val;
        ll lazy;

        void apply([[maybe_unused]] ll l, [[maybe_unused]] ll r) {
            val = r - l - val;
            lazy ^= 1;
        }

        static node unite(const node &a, const node &b) {
            return node{
                    a.val + b.val,
                    NO_OPERATION
            };
        }
    };

    static inline constexpr node NEUTRAL_ELEMENT = {DEFAULT_VALUE, NO_OPERATION};

    ll size;
    vector<node> tree;

    explicit segtree(ll n) {
        size = 1ll;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
    }

    explicit segtree(vector<ll> &a) : segtree(ll(a.size())) {
        build(a, 0, 0, size);
    }

    void print() {
        for (ll i = 1, j = 0; j < ll(tree.size()); i <<= 1) {
            ll c = 0;
            while (c++ < i) cout << tree[j].val << ',' << tree[j++].lazy << ' ';
            cout << '\n';
        }
    }

    inline void push(ll x, ll lx, ll rx) {
        if (rx - lx == 1 || tree[x].lazy == NO_OPERATION) return;

        ll mid = lx + (rx - lx) / 2;
        tree[2 * x + 1].apply(lx, mid);
        tree[2 * x + 2].apply(mid, rx);
        tree[x].lazy = NO_OPERATION;
    }

    inline void pull(ll x) {
        tree[x] = node::unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<ll> &a, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            if (lx < ll(a.size())) tree[x] = {a[lx], NO_OPERATION};
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(ll l, ll r, ll x, ll lx, ll rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            tree[x].apply(lx, rx);
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        modify(l, r, 2 * x + 1, lx, mid);
        modify(l, r, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(ll l, ll r) {
        modify(l, r, 0, 0, size);
    }

    ll get(ll k, ll x, ll lx, ll rx) {
        push(x, lx, rx);
        if (rx - lx == 1) return lx;
        if (tree[x].val == k) return rx;

        ll mid = lx + (rx - lx) / 2;
        ll res;
        push(2 * x + 1, lx, mid);
        push(2 * x + 2, mid, rx);
        if (tree[2 * x + 1].val > k) res = get(k, 2 * x + 1, lx, mid);
        else res = get(k - tree[2 * x + 1].val, 2 * x + 2, mid, rx);
        pull(x);
        return res;
    }

    ll get(ll k) {
        return get(k, 0, 0, size);
    }

};

auto solve() {
    ll N, M;
    cin >> N >> M;

    vector<ll> A(N, 0);
    segtree st(A);

    for (ll _ = 0; _ < M; ++_) {
        char c;
        cin >> c;

        if (c == '1') {
            ll l, r;
            cin >> l >> r;

            st.modify(l, r);
        } else if (c == '2') {
            ll k;
            cin >> k;

            cout << st.get(k) << '\n';
        }
    }
}

int main() {
    solve();
}