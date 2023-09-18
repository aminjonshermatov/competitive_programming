#include <bits/stdc++.h>

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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> v2ost(n);
    vector<vector<int>> ost2v(m);
    for (int i = 0; i < m; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int v; cin >> v, --v;
            v2ost[v].emplace_back(i);
            ost2v[i].emplace_back(v);
        }
    }

    int s, f; cin >> s >> f, --s, --f;
    vector<int> dist(n, inf);
    queue<tuple<int, int, int>> q;
    dist[s] = 0;
    for (auto ost : v2ost[s]) {
        q.emplace(s, ost, 0);
    }
    while (!q.empty()) {
        auto [v, ost, d] = q.front(); q.pop();
        if (dist[v] > d) continue;

        for (auto nost : v2ost[v]) {
            for (auto u : ost2v[nost]) if (u != v) {
                if (dist[u] > dist[v] + 1) {
                    dist[u] = dist[v] + 1;
                    q.emplace(u, nost, d + 1);
                }
            }
        }
    }
    cout << (dist[f] == inf ? -1 : dist[f] - 1) << '\n';
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