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

const int MAX_N = 1e5 + 1;
i64 dp[MAX_N];

void solve() {
    int n; cin >> n;
    cout << dp[n] << '\n';
}

//#define TIME

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef TIME
    auto start = chrono::steady_clock::now();
#endif

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 5;

    for (int i = 3; i < MAX_N; ++i) dp[i] = dp[i - 1] * 3 - dp[i - 2] * 3 + dp[i - 3] + 1 + !(i & 1);

    int t = 1;
    //cin >> t;
    while (t--) solve();

#ifdef TIME
    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
}