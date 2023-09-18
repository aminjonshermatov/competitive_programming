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

inline auto get_first(int x) { return x / 1000; }
inline auto get_last(int x) { return x % 10; }

inline void shift_cyclic_right(int &x) {
    x = (x % 10) * 1000 + x / 10;
}

inline void shift_cyclic_left(int &x) {
    x = (x % 1000) * 10 + (x / 1000);
}

void solve() {
    int s, f;
    cin >> s >> f;

    map<int, int> prv;
    map<int, int> dist;
    for (int i = 1000; i <= 9999; ++i) dist[i] = inf;
    queue<int> q;
    q.emplace(s);
    dist[s] = 0;
    while (!q.empty()) {
        auto v = q.front(); q.pop();
        if (v == f) break ;
        int u = v;
        if (get_first(u) != 9) {
            u += 1000;
            if (dist[u] > dist[v] + 1) {
                dist[u] = dist[v] + 1;
                q.emplace(u);
                prv[u] = v;
            }
            u -= 1000;
        }
        u = v;
        if (get_last(u) != 1) {
            --u;
            if (dist[u] > dist[v] + 1) {
                dist[u] = dist[v] + 1;
                q.emplace(u);
                prv[u] = v;
            }
            ++u;
        }
        u = v;
        shift_cyclic_right(u);
        if (dist[u] > dist[v] + 1) {
            dist[u] = dist[v] + 1;
            q.emplace(u);
            prv[u] = v;
        }
        u = v;
        shift_cyclic_left(u);
        if (dist[u] > dist[v] + 1) {
            dist[u] = dist[v] + 1;
            q.emplace(u);
            prv[u] = v;
        }
    }

    vector<int> path;
    for (auto cur = f; cur != s; path.emplace_back(cur), cur = prv[cur]) { }
    path.emplace_back(s);
    reverse(path.begin(), path.end());
    for (auto &x : path) cout << x << '\n';
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