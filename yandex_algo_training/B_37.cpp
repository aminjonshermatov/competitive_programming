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
    int n; cin >> n;
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }
    int s, f; cin >> s >> f, --s, --f;
    vector<int> prv(n, -1);
    vector<int> dist(n, inf);
    dist[s] = 0;
    queue<int> q;
    q.emplace(s);
    while (!q.empty()) {
        auto v = q.front(); q.pop();
        for (int u = 0; u < n; ++u) if (adj[v][u] && dist[u] > dist[v] + 1) {
                dist[u] = dist[v] + 1;
                prv[u] = v;
                q.emplace(u);
            }
    }
    if (dist[f] == inf) {
        cout << -1 << '\n';
        return;
    }
    cout << dist[f] << '\n';
    if (dist[f] > 0) {
        vector<int> path;
        for (auto v = f; v != -1; path.emplace_back(v), v = prv[v]) { }
        reverse(path.begin(), path.end());
        for (auto x : path) cout << x + 1 << ' ';
        cout << '\n';
    }
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