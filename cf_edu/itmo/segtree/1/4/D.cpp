//
// Created by aminjon on 10/22/22.
//
#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define F first
#define S second
#define mk make_pair
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (ll)((x).size())

#define rep(i, a, b) for (ll i = (a); (i) < (b); ++(i))
#define forr(el, cont) for (auto &(el) : (cont))
#define read(k) ll k; cin >> k

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

template<typename T>
using V = vector<T>;

template<typename T = ll>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

[[maybe_unused]] mt19937 rnd(143);

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

struct segtree {

    ll size{};
    V<array<ll, 41>> tree;

    static auto make_zero_array() {
        array<ll, 41> cnt{};
        fill(all(cnt), 0);
        return cnt;
    }

    void init(ll n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, make_zero_array());
    }

    void build(V<ll> &a, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            if (lx < sz(a)) ++tree[x][a[lx]];
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        rep(i, 1, 41) tree[x][i] = tree[2 * x + 1][i] + tree[2 * x + 2][i];
    }

    void build(V<ll> &a) {
        init(sz(a));
        build(a, 0, 0, size);
    }

    void set(ll i, ll old_v, ll new_v, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            --tree[x][old_v];
            ++tree[x][new_v];
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        if (i < mid)    set(i, old_v, new_v, 2 * x + 1, lx, mid);
        else            set(i, old_v, new_v, 2 * x + 2, mid, rx);
        rep(j, 1, 41) tree[x][j] = tree[2 * x + 1][j] + tree[2 * x + 2][j];
    }

    void set(ll i, ll old_v, ll new_v) {
        set(i, old_v, new_v, 0, 0, size);
    }

    void get_union(ll l, ll r, ll x, ll lx, ll rx, array<ll, 41> &res) {
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            rep(j, 1, 41) res[j] += tree[x][j];
            return;
        }

        ll mid = lx + (rx - lx) / 2;
        get_union(l, r, 2 * x + 1, lx, mid, res);
        get_union(l, r, 2 * x + 2, mid, rx, res);
    }

    ll get_distinct_count(ll l, ll r) {
        auto cnt = make_zero_array();
        get_union(l, r, 0, 0, size, cnt);
        return count_if(all(cnt), [](auto c) { return c > 0; });
    }

};

void solve() {
    read(N);
    read(Q);

    V<ll> A(N);
    forr(a, A) cin >> a;

    segtree st;
    st.build(A);

    rep(_, 0, Q) {
        read(tp);

        if (tp == 1) {
            read(l);
            read(r);
            cout << st.get_distinct_count(--l, r) << '\n';
        } else {
            read(i);
            read(v);
            --i;
            st.set(i, A[i], v);
            A[i] = v;
        }
    }
}

bool is_multi = false;

int main() {
    // auto start = chrono::steady_clock::now();

    IOS

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // cout << "Case #" << tc << ": ";
        solve();
        cout << '\n';
    }

    // auto finish = chrono::steady_clock::now();
    // auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}