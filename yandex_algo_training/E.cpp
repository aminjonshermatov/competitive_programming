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

struct point2d {
    int x, y;
    bool operator==(const point2d &other) const {
        return x == other.x && y == other.y;
    }
};

struct Dir {
    int dx, dy;
};
inline constexpr array<Dir, 8> dirs{
        Dir{+0, -1},
        Dir{+1, -1},
        Dir{+1, +0},
        Dir{+1, +1},
        Dir{+0, +1},
        Dir{-1, +1},
        Dir{-1, +0},
        Dir{-1, -1},
};
inline constexpr array<int, 8> INF{
        inf, inf, inf, inf,
        inf, inf, inf, inf
};

void solve() {
    int h, w; cin >> h >> w;

    auto ok = [&](int x, int y) -> bool {
        return clamp(x, 0, w - 1) == x && clamp(y, 0, h - 1) == y;
    };

    vector<string> g(h);
    for (int i = h - 1; i >= 0; --i) cin >> g[i];
    point2d start{}, finish{};
    cin >> start.x >> start.y; --start.x, --start.y;
    cin >> finish.x >> finish.y; --finish.x, --finish.y;

    queue<pair<point2d, int>> q;

    vector<vector<array<int, 8>>> dist(h, vector<array<int, 8>>(w, INF));
    for (int dir_id = 0; dir_id < dirs.size(); ++dir_id) {
        q.emplace(start, dir_id);
        dist[start.y][start.x][dir_id] = 1;
    }

    int ans = inf;
    while (!q.empty()) {
        auto [p, id] = q.front(); q.pop();
        auto [x, y] = p;
        if (point2d{x, y} == finish) ans = min(ans, dist[y][x][id]);
        for (int d_id = 0; d_id < dirs.size(); ++d_id) {
            auto [dx, dy] = dirs[d_id];
            auto nx = x + dx;
            auto ny = y + dy;
            if (!ok(nx, ny) || g[ny][nx] == 'X') continue ;
            auto cost = id != d_id;
            if (dist[y][x][id] + cost >= ans) continue ;
            if (dist[ny][nx][d_id] > dist[y][x][id] + cost) {
                dist[ny][nx][d_id] = dist[y][x][id] + cost;
                q.emplace(point2d{nx, ny}, d_id);
            }
        }
    }

    cout << (ans == inf ? -1 : ans) << '\n';
}

//#define MEASURE_TIME

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef MEASURE_TIME
    auto start = chrono::steady_clock::now();
#endif

    int t = 1;
    //cin >> t;
    while (t--) solve();

#ifdef MEASURE_TIME
    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
}