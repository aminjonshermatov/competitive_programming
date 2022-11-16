#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
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

template<typename T = ll>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

[[maybe_unused]] mt19937 rnd(143);

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;

    V<V<ll>> dist(n, V<ll>(n, inf));

    rep(_, 0, m) {
        ll a, b, w;
        cin >> a >> b >> w;
        --a, --b;

        dist[a][b] = min(dist[a][b], w);
        dist[b][a] = min(dist[b][a], w);
    }

    rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) {
        if (dist[i][k] != inf && dist[k][j] != inf) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
    rep(i, 0, n) dist[i][i] = 0;

    rep(_, 0, q) {
        ll a, b;
        cin >> a >> b;
        --a, --b;

        cout << (dist[a][b] == inf ? -1 : dist[a][b]) << '\n';
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
