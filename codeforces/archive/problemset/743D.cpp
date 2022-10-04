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

const ll MAX_N = 2e5 + 11;
ll A[MAX_N], sum[MAX_N], best[MAX_N];
V<ll> G[MAX_N];

ll ans = -inf;

void dfs(ll v, ll p = -1) {
    ll mx1 = -inf, mx2 = -inf;
    sum[v] = A[v];
    for (auto u : G[v]) if (u != p) {
            dfs(u, v);
            sum[v] += sum[u];
            if (best[u] > mx1) {
                mx2 = mx1;
                mx1 = best[u];
            } else if (best[u] > mx2) {
                mx2 = best[u];
            }
    }

    if (mx2 != -inf) ans = max(ans, mx1 + mx2);
    best[v] = max(sum[v], mx1);
}

void solve() {
    read(N);
    rep(i, 0, N) cin >> A[i];
    rep(i, 1, N) {
        read(p);
        read(q);
        --p, --q;
        G[p].emplace_back(q);
        G[q].emplace_back(p);
    }

    fill(sum, sum + N, 0);
    fill(best, best + N, -inf);
    dfs(0, -1);
//    rep(i, 0, N) cout << sum[i] << " \n"[i == N - 1];
//    rep(i, 0, N) cout << best[i] << " \n"[i == N - 1];

    if (ans == -inf) cout << "Impossible";
    else cout << ans;
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