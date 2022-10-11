//
// Created by aminjon on 10/11/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

struct segtree {

    struct node {
        ll seg, pref, suf, sum;
    };

    node ZERO = {0, 0, 0, 0};

    vector<node> tree;
    ll size{};

    void init(ll n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, ZERO);
    }

    static node combine(node l, node r) {
        return {
            max(max(l.seg, r.seg), l.suf + r.pref),
            max(l.pref, l.sum + r.pref),
            max(r.suf, r.sum + l.suf),
            l.sum + r.sum
        };
    }

    static node one_element(ll v) {
        return {max(v, ll(0)), max(v, ll(0)), max(v, ll(0)), v};
    }

    void build(vector<ll> &a, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) tree[x] = one_element(a[lx]);
            return;
        }

        ll m = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<ll> &a) {
        init((ll)a.size());
        build(a, 0, 0, size);
    }

    void set(ll i, ll v, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            tree[x] = one_element(v);
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

    node max_seg(ll l, ll r, ll x, ll lx, ll rx) {
        if (l >= rx || r <= lx) return ZERO;
        if (l <= lx && rx <= r) return tree[x];

        ll m = lx + (rx - lx) / 2;
        return combine(max_seg(l, r, 2 * x + 1, lx, m), max_seg(l, r, 2 * x + 2, m, rx));
    }

    node max_seg(ll l, ll r) {
        return max_seg(l, r, 0, 0, size);
    }

};

auto solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);

    for (ll i = 0; i < N; ++i) cin >> A[i];

    segtree st;
    st.build(A);

    cout << st.tree[0].seg << '\n';
    for (ll i = 0; i < M; ++i) {
        ll idx, v;
        cin >> idx >> v;
        st.set(idx, v);
        cout << st.tree[0].seg << '\n';
    }
}

auto main() -> int32_t {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
}