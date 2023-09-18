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

inline constexpr array<int, 6> dz{+0, +0, +0, +0, -1, +1};
inline constexpr array<int, 6> dy{+0, +0, -1, +1, +0, +0};
inline constexpr array<int, 6> dx{-1, +1, +0, +0, +0, +0};
void solve() {
    int n; cin >> n;

    auto ok = [&](int z, int y, int x) -> bool { return clamp(z, 0, n - 1) == z && clamp(y, 0, n - 1) == y && clamp(x, 0, n - 1) == x; };

    vector<vector<vector<char>>> adj(n, vector<vector<char>>(n, vector<char>(n)));
    using point_t = tuple<int, int, int>;
    point_t start;
    for (int z = 0; z < n; ++z) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> adj[z][i][j];
                if (adj[z][i][j] == 'S') start = tuple(z, i, j);
            }
        }
    }

    queue<pair<point_t, int>> q;
    q.emplace(start, 0);
    while (!q.empty()) {
        auto [p, dist] = q.front(); q.pop();
        auto [z, y, x] = p;

        if (z == 0) {
            cout << dist << '\n';
            return;
        }

        for (int k = 0; k < dz.size(); ++k) {
            auto nz = z + dz[k];
            auto ny = y + dy[k];
            auto nx = x + dx[k];
            if (ok(nz, ny, nx) && adj[nz][ny][nx] != '#') {
                q.emplace(point_t(nz, ny, nx), dist + 1);
                adj[nz][ny][nx] = '#';
            }
        }
    }
    assert(false);
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