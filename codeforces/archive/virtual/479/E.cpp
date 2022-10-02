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

void solve() {
    read(N);
    read(M);

    V<set<ll>> G(N);
    V<ll> C(N, 0), prev(N, -1);
    // 0-didn't seen
    // 1-in progress
    // 2-done

    map<ll, set<ll>> vert;

    rep (i, 0, M) {
        read(a);
        read(b);

        --a, --b;
        G[a].insert(b);
        G[b].insert(a);
    }

    int comp_count = 0;
    function<bool(ll, ll)> dfs = [&](ll v, ll p) -> bool {
        C[v] = 1;
        vert[comp_count].insert(v);
        bool has_cycle = false;

        for (auto u : G[v]) {
            if (u == p) continue;
            if (C[u] == 0) {
                has_cycle |= dfs(u, v);
                prev[u] = v;
            } else if (C[u] == 1) {
                has_cycle = true;
            }
        }

        C[v] = 2;
        return has_cycle;
    };


    ll ans = 0;
    rep (i, 0, N) {
        if (C[i] == 0) {
            ++comp_count;
            if (dfs(i, -1)) {
                bool ok = true;
                forr(e, vert[comp_count]) {
                    ok = G[e].size() == 2;
                    if (!ok) break;
                }
                if (ok) ++ans;

            }
        }
    }
    cout << ans;
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