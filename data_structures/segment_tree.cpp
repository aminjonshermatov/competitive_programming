//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct segtree {

    static inline constexpr ll DEFAULT_VALUE = 0ll;
    static inline constexpr ll NO_OPERATION = 0ll;

    struct node {
        ll val = DEFAULT_VALUE;
        ll lazy = NO_OPERATION;

        void apply([[maybe_unused]] ll l, [[maybe_unused]] ll r, ll v) {
            val += v;
            lazy += v;
        }

        static node unite(const node &a, const node &b) {
            return node{
                    min(a.val, b.val),
                    NO_OPERATION
            };
        }
    };

    static inline constexpr node NEUTRAL_ELEMENT = {numeric_limits<ll>::max(), NO_OPERATION};

    ll size;
    vector<node> tree;

    explicit segtree(ll n) {
        size = 1ll;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, {});
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
        tree[2 * x + 1].apply(lx, mid, tree[x].lazy);
        tree[2 * x + 2].apply(mid, rx, tree[x].lazy);
        tree[x].lazy = NO_OPERATION;
    }

    inline void pull(ll x) {
        tree[x] = node::unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void modify(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            tree[x].apply(lx, rx, v);
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(ll l, ll r, ll v) {
        modify(l, r, v, 0, 0, size);
    }

    node get(ll l, ll r, ll x, ll lx, ll rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return tree[x];

        ll mid = lx + (rx - lx) / 2;
        auto res = node::unite(get(l, r, 2 * x + 1, lx, mid),
                               get(l, r, 2 * x + 2, mid, rx));
        pull(x);
        return res;
    }

    ll get(ll l, ll r) {
        auto res = get(l, r, 0, 0, size);
        return res.val;
    }

};