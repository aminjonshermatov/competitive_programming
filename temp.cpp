#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <typeinfo>

#include <vector>
#include <array>
#include <valarray>
#include <queue>
#include <stack>
#include <set>
#include <map>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <cmath>
#include <climits>

using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef pair<ll, ll> pll;
typedef unsigned long long ull;
typedef long double ld;

#define fi first
#define se second
#define P pair
#define mp make_pair
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


[[maybe_unused]] mt19937 rnd(143);

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;

    vector<vector<pair<ll, pll>>> g(n);
    rep(i, 0, m) {
        ll u, v, a, b;
        cin >> u >> v >> a >> b;
        --u, --v;

        ll gcd = __gcd(a, b);
        g[u].eb(v, mp(a / gcd, b / gcd));
    }

    vector<bool> used(n, false);
    vector<ll> order;
    order.reserve(n);
    auto top_sort = [&](auto &self, ll v) -> void {
        used[v] = true;

        for (auto [u, _] : g[v]) if (!used[u]) self(self, u);
        order.eb(v);
    };
    top_sort(top_sort, 0);

    reverse(all(order));
    fill(all(used), false);
    used[0] = true;
    pll def_inf = pll{1e9 + 10, 1};
    vector<pll> min_r(n, def_inf);
    pll def_min_inf = pll{1, 1e9 + 10};
    min_r[n - 1] = def_min_inf;

    pll mx = def_min_inf;
    for (auto v : order) {
        if (used[v]) {
            for (auto [u, c] : g[v]) {
                cout << v << ' ' << u << '\n';
                used[u] = true;
                if (v == 0) min_r[u] = c;
                else {
                    pll t = min_r[v].fi * c.se > min_r[v].se * c.fi ? c : min_r[v];
                    if (min_r[u] == def_inf) min_r[u] = t;
                    else {
                        if (min_r[u].fi * t.se > min_r[u].se * t.fi) min_r[u] = t;
                    }
                    if (u + 1 == n) {
                        if (mx.fi * min_r[u].se < mx.se * min_r[u].fi) mx = min_r[u];
                        min_r[u] = def_min_inf;
                    }
                }
            }
        }
    }

    rep(v, 0, n) cout << min_r[v].fi << ' ' << min_r[v].se << '\n';
    cout << mx.fi << ' ' << mx.se << '\n';

    rep(i, 0, q) {
        pll p;
        cin >> p.fi >> p.se;

        cout << (p.fi * mx.fi > p.se * mx.se ? "YES" : "NO") << '\n';
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