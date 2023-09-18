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

inline constexpr array<int, 8> dy{-2, -2, -1, -1, +1, +1, +2, +2};
inline constexpr array<int, 8> dx{-1, +1, -2, +2, -2, +2, -1, +1};
void solve() {
    int n, m, s, t, qq;
    cin >> n >> m >> s >> t >> qq;
    --s, --t;

    vector<string> g(n, string(m, '#'));
    for (int _ = 0; _ < qq; ++_) {
        int y, x; cin >> y >> x, --y, --x;
        g[y][x] = '.';
    }
    vector<vector<int>> dist(n, vector<int>(m, inf));
    auto ok = [&](int i, int j) -> bool { return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j; };
    queue<pii> q;
    q.emplace(s, t);
    dist[s][t] = 0;
    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        for (int k = 0; k < 8; ++k) {
            auto ni = i + dy[k];
            auto nj = j + dx[k];
            if (ok(ni, nj) && (g[ni][nj] == '.' || g[ni][nj] == '#') && dist[ni][nj] > dist[i][j] + 1) {
                g[ni][nj] = g[ni][nj] == '.' ? ',' : '?';
                dist[ni][nj] = dist[i][j] + 1;
                q.emplace(ni, nj);
            }
        }
    }

    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) if (i != s || j != t) {
            if (g[i][j] == ',' || g[i][j] == '.') {
                if (g[i][j] == '.' || dist[i][j] == inf) {
                    cout << -1 << '\n';
                    return;
                }
                ans += dist[i][j];
            }
        }
    }
    cout << ans << '\n';
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