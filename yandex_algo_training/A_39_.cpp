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
inline constexpr auto dinf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n + m);
    vector<pair<int, int>> E(m);
    int mv = n;
    for (int _ = 0; _ < m; _++) {
        int u, v; cin >> u >> v, --u, --v;

        auto uv = mv++;
        g[u].emplace_back(uv);
        g[uv].emplace_back(u);
        g[v].emplace_back(uv);
        g[uv].emplace_back(v);
        E[_] = {u, v};
    }

    int k; cin >> k;
    vector<int> rs(k);
    for (auto &r : rs) cin >> r, --r;
    sort(rs.begin(), rs.end());
    rs.erase(unique(rs.begin(), rs.end()), rs.end());

    auto ans = dinf;
    for (int V = 0; V < mv; ++V) {
        queue<int> q;
        vector<int> dist(mv, inf);
        q.emplace(V);
        dist[V] = 0;
        while (!q.empty()) {
            auto v = q.front(); q.pop();
            for (auto u : g[v]) if (dist[v] + 1 < dist[u]) {
                    dist[u] = dist[v] + 1;
                    q.emplace(u);
                }
        }

        if (any_of(rs.begin(), rs.end(), [&](int r) { return dist[r] == inf; })) continue ;
        ld d = 0;
        array<int, 2> rem{};
        for (auto r : rs) d = max<ld>(d, dist[r]), ++rem[(dist[r] >> 1) & 1];
        cout << "rems: " << rem[0] << ' ' << rem[1] << '\n';
        if (rem[0] != rs.size() && rem[1] != rs.size()) {
            for (auto [u, v] : E) if (dist[u] != inf && dist[v] != inf) {
                    d = max<ld>(d, max(dist[u], dist[v]) + 1);
                }
        }

        cout << V << ' ' << d << '\n';
        ans = min(ans, d / 2);
    }
    cout << (ans == dinf ? -1 : ans) << '\n';
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