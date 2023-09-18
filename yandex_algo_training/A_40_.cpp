#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

const int N = 2022;
const int K = 2022;

vector<int> g2k[N];
vector<int> dist[N];
vector<int> k2g[K][N];

void solve() {
    int n, k; cin >> n >> k;

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    for (auto &r : dist) r.assign(k, inf);

    for (int kk = 0; kk < k; ++kk) {
        int x; cin >> x;
        while (x--) {
            int u, v; cin >> u >> v, --u, --v;
            k2g[kk][u].emplace_back(v);
            k2g[kk][v].emplace_back(u);
            g2k[u].emplace_back(kk);
            g2k[v].emplace_back(kk);
            if (u == 0 || v == 0) {
                dist[0][kk] = 1;
                pq.emplace(1, 0, kk);
            }
        }
    }

    int ans = inf;
    while (!pq.empty()) {
        auto [d, v, kk] = pq.top(); pq.pop();
        if (d >= ans) continue;
        if (v == n - 1) ans = min(ans, d);

        for (auto kkk : g2k[v]) {
            for (auto u : k2g[kkk][v]) if (dist[u][kkk] > dist[v][kk] + (kkk != kk)) {
                //cout << v + 1 << '-' << u + 1 << ' ' << d + (kk != kkk) << '\n';
                dist[u][kkk] = dist[v][kk] + (kkk != kk);
                pq.emplace(dist[u][kkk], u, kkk);
            }
        }
    }

    cout << (ans == inf ? -1 : ans) << '\n';
}

//#define TIME

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef TIME
    auto start = chrono::steady_clock::now();
#endif

    int t = 1;
    //cin >> t;
    while (t--) solve();

#ifdef TIME
    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
}