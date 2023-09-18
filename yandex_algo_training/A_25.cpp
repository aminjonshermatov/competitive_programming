#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<i64>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

void solve() {
    i64 n, a, b; cin >> n >> a >> b;

    vector<i64> cache(n + 1, -1);
    cache[1] = 0;
    auto dp = [&](auto f, i64 k) -> i64 {
        if (cache[k] != -1) return cache[k];
        i64 ans = inf;
        for (int i = 1; i < k; ++i) {
            ans = min(ans, max(a + f(f, i), b + f(f, k - i)));
        }
        assert(ans != inf);
        return cache[k] = ans;
    };
    cout << dp(dp, n) << '\n';
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
