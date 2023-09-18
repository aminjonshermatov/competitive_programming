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

const int MAX_N = 1e6 + 1;
vector<int> cubes;
int dp[MAX_N];

void solve() {
    int n; cin >> n;
    cout << dp[n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    //auto start = chrono::steady_clock::now();

    for (int k = 1; ; ++k) {
        auto cube = k * k * k;
        if (cube > MAX_N) break;
        cubes.emplace_back(cube);
    }
    for (int s = 1; s < MAX_N; ++s) dp[s] = inf;
    dp[0] = 0;
    for (int s = 0; s < MAX_N; ++s) {
        for (auto ss : cubes) {
            if (s + ss < MAX_N) dp[s + ss] = min(dp[s + ss], dp[s] + 1);
            else break;
        }
    }
    /*auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";*/
    int t = 1;
    //cin >> t;
    while (t--) solve();
}