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
typedef unsigned long long ull;
typedef long double ld;

#define F first
#define S second
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
    ll N, M, K;
    cin >> N >> M >> K;

    V<V<pll>> G(N + 1);
    V<V<ll>> same(N + 1);

    string s(M, '0');
    rep(i, 0, M) {
        read(p); read(q);

        G[p].pb({q, i});
        G[q].pb({p, i});
    }

    V<ll> dist(N + 1, inf);
    queue<ll> q;
    q.push(1);
    dist[1] = 0;
    while (!q.empty()) {
        auto v = q.front(); q.pop();

        for (auto [u, i] : G[v]) {
            if (dist[v] + 1 < dist[u]) {
                dist[u] = dist[v] + 1;
                same[u].clear();
                same[u].eb(i);
                q.push(u);
            } else if (dist[v] + 1 == dist[u]) {
                same[u].eb(i);
            }
        }
    }

    V<string> ans;
    auto rec = [&](auto &self, ll v) {
        if (v == N + 1) {
            ans.pb(s);
            return;
        }

        for (auto j : same[v]) {
            if (sz(ans) == K) break;
            s[j] = '1';
            self(self, v + 1);
            s[j] = '0';
        }
    };

    rec(rec, 2);

    cout << sz(ans) << '\n';
    forr(a, ans) cout << a << '\n';
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
