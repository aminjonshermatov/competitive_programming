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

inline constexpr array<int, 5> dk{1, 0, -1, 0, 1};
using pii = pair<int, int>;

i64 binpow(i64 a, i64 n) {
    i64 ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        a *= a, n >>= 1;
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    vector<set<int>> g(n);
    vector<int> deg(n, 0);
    for (int v = 0; v < n; ++v) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int u; cin >> u, --u;
            g[v].insert(u);
            ++deg[u];
        }
    }

    set<int> q;
    for (int v = 0; v < n; ++v) if (deg[v] == 0) q.insert(-v);

    vector<int> order;
    order.reserve(n);
    while (!q.empty()) {
        auto v = *q.begin(); q.erase(q.begin());
        v *= -1;
        order.emplace_back(v);
        for (auto u : g[v]) if (--deg[u] == 0) q.insert(-u);
    }

    reverse(order.begin(), order.end());
    for (auto u : order) cout << u + 1 << ' ';
    cout << '\n';
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
