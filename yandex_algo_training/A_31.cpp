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

inline constexpr array<int, 5> dk{1, 0, -1, 0, 1};
void solve() {
    int n; cin >> n;

    auto ok = [&](int i, int j) { return clamp(i, 0, n - 1) == i && clamp(j, 0, n - 1) == j; };

    vector<string> g(n);
    for (auto &r : g) cin >> r;

    queue<pii> q;
    {
        int i, j; cin >> i >> j;
        --i, --j;
        q.emplace(i, j);
        g[i][j] = '*';
    }

    int ans = 1;
    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        for (int k = 0; k < 4; ++k) {
            auto ni = i + dk[k];
            auto nj = j + dk[k + 1];
            if (!ok(ni, nj) || g[ni][nj] == '*') continue;
            g[ni][nj] = '*';
            ++ans;
            q.emplace(ni, nj);
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
