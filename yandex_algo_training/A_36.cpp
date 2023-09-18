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

pair<int, int> get_coor() {
    char x, y;
    cin >> x >> y;
    return {x - 'a', y - '1'};
}

inline bool ok(pii &r, pii &g) {
    return clamp(r.first, 0, 7) == r.first && clamp(r.second, 0, 7) == r.second
        && clamp(g.first, 0, 7) == g.first && clamp(g.second, 0, 7) == g.second;
}

inline constexpr array<int, 8> dy{-2, -2, -1, -1, +1, +1, +2, +2};
inline constexpr array<int, 8> dx{-1, +1, -2, +2, -2, +2, -1, +1};
bool can_beat(pii &r, pii &g) {
    for (int i = 0; i < dy.size(); ++i) {
        auto nr = pair(r.first + dx[i], r.second + dy[i]);
        if (nr == g) return true;
    }
    for (int i = 0; i < dy.size(); ++i) {
        auto ng = pair(g.first + dx[i], g.second + dy[i]);
        if (r == ng) return true;
    }
    return false;
}


void solve() {
    auto r = get_coor();
    auto g = get_coor();

    queue<pair<pair<pii, pii>, int>> q;
    q.emplace(pair(r, g), 0);
    set<pair<pii, pii>> seen;
    seen.emplace(r, g);
    while (!q.empty()) {
        auto [pp, d] = q.front(); q.pop();
        auto [rr, gg] = pp;
        if (rr == gg) {
            cout << d << '\n';
            return;
        }
        for (int i = 0; i < dy.size(); ++i) {
            for (int j = 0; j < dy.size(); ++j) {
                auto nr = pair(rr.first + dx[i], rr.second + dy[i]);
                auto ng = pair(gg.first + dx[j], gg.second + dy[j]);
                if (!ok(nr, ng)) continue ;
                if (can_beat(nr, ng)) continue ;
                auto [_, inserted] = seen.insert(pair(nr, ng));
                if (inserted) {
                    q.emplace(pair(nr, ng), d + 1);
                }
            }
        }
    }

    cout << -1 << '\n';
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