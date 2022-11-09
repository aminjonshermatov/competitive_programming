//
// Created by aminjon on 11/9/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct segtree {

    static inline constexpr ll DEFAULT_VALUE = 0ll;

    struct node {
        ll sum;
        ll pref;
        ll suf;
        ll mx;
        ll lazy;
        bool has_lazy;

        void apply([[maybe_unused]] ll l, [[maybe_unused]] ll r, ll v) {
            sum = (r - l) * v;
            pref = suf = mx = (v > 0 ? sum : 0);
            lazy = v;
            has_lazy = true;
        }

        static node unite(const node &a, const node &b) {
            return node{
                    a.sum + b.sum,
                    max(a.pref, a.sum + b.pref),
                    max(b.suf, a.suf + b.sum),
                    max(max(a.mx, b.mx), a.suf + b.pref),
                    0,
                    false
            };
        }
    };

    static inline constexpr node NEUTRAL_ELEMENT = {0, 0, 0, 0, 0, false};

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
            while (c++ < i) cout << '(' << tree[j].sum << ',' << tree[j].pref << ',' << tree[j].suf << ',' << tree[j].mx << ',' << tree[j++].lazy << ") ";
            cout << '\n';
        }
    }

    inline void push(ll x, ll lx, ll rx) {
        if (rx - lx == 1 || !tree[x].has_lazy) return;

        ll mid = lx + (rx - lx) / 2;
        tree[2 * x + 1].apply(lx, mid, tree[x].lazy);
        tree[2 * x + 2].apply(mid, rx, tree[x].lazy);
        tree[x].has_lazy = false;
    }

    inline void pull(ll x) {
        tree[x] = node::unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<ll> &a, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            if (lx < ll(a.size())) {
                ll mx = max(a[lx], ll(0));
                tree[x] = {a[lx], mx, mx, mx, 0, false};
            }
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
        return get(l, r, 0, 0, size).mx;
    }

};

auto solve() {
    ll n, m;
    cin >> n >> m;

    vector<ll> A(n, 0);
    segtree st(A);

    for (ll q = 0; q < m; ++q) {
        ll l, r, v;
        cin >> l >> r >> v;

        st.modify(l, r, v);
        cout << st.get(0, n) << '\n';
    }
}

int main() {
    solve();
}