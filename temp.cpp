#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
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

const ll max_n = 2e5 + 11;
V<ll> G[max_n];
unordered_set<ll> in[max_n];
ll colored[max_n];

void dfs(ll v, ll p) {
    if (p != -1) in[p].insert(v);
    forr(u, G[v]) if (u != p) {
        if (in[v].count(u) == 0) dfs(u, v);
    }
}

void solve() {
    read(N);
    read(K);

    rep(i, 0, K) {
        read(t);
        colored[t] = true;
    }

    rep(i, 1, N) {
        read(p);
        read(q);
        G[p].emplace_back(q);
        G[q].emplace_back(p);
    }

    rep(i, 1, N + 1) if (colored[i]) {
        dfs(i, -1);
    }

    V<ll> ans;
    rep(v, 1, N + 1) if (!colored[v]) {
        bool ok = true;
        forr(u, G[v]) {
            if (in[u].count(v) == 0) { ok = false; break; }
        }
        if (ok) ans.emplace_back(v);
    }

    sort(all(ans));
    cout << sz(ans) << '\n';
    forr(a, ans) cout << a << ' ';
    cout << '\n';
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