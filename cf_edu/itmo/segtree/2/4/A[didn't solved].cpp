//
// Created by aminjon on 11/11/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct segtree {

    static inline constexpr ll DEFAULT_VALUE = 0ll;
    static inline constexpr ll DEFAULT_LAZY = 0ll;
    static inline constexpr int NO_OPERATION = 2;

    struct node {
        ll val;
        ll lazy;
        int type; // 1-assign, 0-add, 2-no operation

        void apply(ll l, ll r, ll v, int req_type) {
            if (req_type == 1) {
                val = (r - l) * v;
                lazy = v;
            } else {
                val += (r - l) * v;
                lazy += v;
            }
            type = req_type;
        }

        static node unite(const node &a, const node &b) {
            return node{
                    a.val + b.val,
                    DEFAULT_LAZY,
                    NO_OPERATION
            };
        }
    };

    static inline constexpr node NEUTRAL_ELEMENT = {DEFAULT_VALUE, DEFAULT_LAZY, NO_OPERATION};

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
            while (c++ < i) cout << '(' << tree[j].val << ',' << tree[j].lazy << ',' << tree[j++].type << ") ";
            cout << '\n';
        }
    }

    inline void push(ll x, ll lx, ll rx) {
        if (rx - lx == 1 || tree[x].type == NO_OPERATION) return;

        ll mid = lx + (rx - lx) / 2;
        tree[2 * x + 1].apply(lx, mid, tree[x].lazy, tree[x].type);
        tree[2 * x + 2].apply(mid, rx, tree[x].lazy, tree[x].type);
        tree[x].lazy = DEFAULT_LAZY;
        tree[x].type = NO_OPERATION;
    }

    inline void pull(ll x) {
        tree[x] = node::unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<ll> &a, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            if (lx < ll(a.size())) tree[x] = {a[lx], DEFAULT_LAZY, NO_OPERATION};
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(ll l, ll r, ll v, int is_assign, ll x, ll lx, ll rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            tree[x].apply(lx, rx, v, is_assign);
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        modify(l, r, v, is_assign, 2 * x + 1, lx, mid);
        modify(l, r, v, is_assign, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(ll l, ll r, ll v, int is_assign) {
        modify(l, r, v, is_assign, 0, 0, size);
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
        return get(l, r, 0, 0, size).val;
    }

};

auto solve() {
    ll N, M;
    cin >> N >> M;

    vector<ll> A(N, 0);
    segtree st(A);

    for (int _ = 0; _ < M; ++_) {
        char c;
        cin >> c;

        ll l, r;
        cin >> l >> r;
        if (c == '1' || c == '2') {
            ll v;
            cin >> v;

            st.modify(l, r, v, c == '1');
        } else {
            cout << st.get(l, r) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}