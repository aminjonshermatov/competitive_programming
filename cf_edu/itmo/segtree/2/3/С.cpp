//
// Created by aminjon on 11/11/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

inline constexpr ll inf = numeric_limits<ll>::max();

struct segtree {

    static inline constexpr ll DEFAULT_VALUE = 0ll;
    static inline constexpr ll NO_OPERATION = 0ll;

    struct node {
        ll val;
        ll lazy;
        ll right;

        void apply([[maybe_unused]] ll l, [[maybe_unused]] ll r, ll v) {
            val += v * (r - l);
            lazy += v;
        }

        static node unite(const node &a, const node &b) {
            return node{
                    max(a.val, b.val),
                    NO_OPERATION,
                    b.right
            };
        }
    };

    static inline constexpr node NEUTRAL_ELEMENT = {DEFAULT_VALUE, NO_OPERATION, inf};

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
            while (c++ < i) cout << '(' << tree[j].val << ',' << tree[j].lazy << ',' << tree[j++].right << ") ";
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

    void build(vector<ll> &a, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            if (lx < ll(a.size())) tree[x] = {a[lx], NO_OPERATION, lx};
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        pull(x);
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

    ll find_first_above(ll v, ll l, ll x, ll lx, ll rx) {
        push(x, lx, rx);
        if (tree[x].val < v || tree[x].right < l) return -1;
        if (rx - lx == 1) return lx;

        ll mid = lx + (rx - lx) / 2;
        auto idx = find_first_above(v, l, 2 * x + 1, lx, mid);
        if (idx == -1) idx = find_first_above(v, l, 2 * x + 2, mid, rx);
        pull(x);
        return idx;
    }

    ll find_first_above(ll v, ll l) {
        return find_first_above(v, l, 0, 0, size);
    }

};

auto solve() {
    ll n, m;
    cin >> n >> m;

    vector<ll> A(n, 0);
    segtree st(A);

    for (ll q = 0; q < m; ++q) {
        char c;
        cin >> c;

        if (c == '1') {
            ll l, r, v;
            cin >> l >> r >> v;

            st.modify(l, r, v);
        } else {
            ll v, l;
            cin >> v >> l;

            cout << st.find_first_above(v, l) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}