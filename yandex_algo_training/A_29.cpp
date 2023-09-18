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
    int M, N; cin >> M >> N;

    map<pii, i64> cache;
    auto dp = [&](auto f, int m, int n) -> i64 {
        if (m <= 0) return 0;
        if (n <= 1) return 1;
        if (auto it = cache.find(pii(m, n)); it != cache.end()) return it->second;
        i64 ans = 0;
        for (int i = 0; i < m; ++i) ans += f(f, m - i, n - 1) + f(f, m - i - 1, n - 1);
        return cache[pii(m, n)] = ans;
    };

    cout << dp(dp, M, N) << '\n';
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
