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

inline constexpr array<int, 4> di{-2, -2, -1, +1};
inline constexpr array<int, 4> dj{+1, -1, -2, -2};
constexpr auto K = di.size();
void solve() {
    int n, m; cin >> n >> m;

    auto ok = [&](int i, int j) { return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j; };
    vector<vector<i64>> dp(n, vector<i64>(m, 0));
    dp[0][0] = 1;

    for (int k = 1; k < n + m - 1; ++k) {
        int i = k, j = 0;
        if (i >= n) {
            i = n - 1;
            j = k - n + 1;
        }
        while (ok(i, j)) {
            for (int nk = 0; nk < K; ++nk) {
                auto ni = i + di[nk];
                auto nj = j + dj[nk];
                if (ok(ni, nj)) dp[i][j] += dp[ni][nj];
            }
            --i, ++j;
        }
    }
    cout << dp[n - 1][m - 1];
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

/*
import sys

#sys.stdin = open('input.txt', 'r')
#sys.stdout = open('output.txt', 'w')

Di = [-2, -2, -1, +1]
Dj = [+1, -1, -2, -2]
def main():
    n, m = map(int, sys.stdin.readline().split())
    def ok(i, j): return 0 <= i < n and 0 <= j < m
    dp = [[0] * m for _ in range(n)]
    dp[0][0] = 1
    for k in range(1, n + m - 1):
        i, j = k, 0
        if i >= n: i, j = n - 1, k - n + 1
        while ok(i, j):
            for di, dj in zip(Di, Dj):
                ni, nj = i + di, j + dj
                if ok(ni, nj): dp[i][j] += dp[ni][nj]
            i, j = i - 1, j + 1
    print(dp[n - 1][m - 1])



if __name__ == '__main__':
    main()
*/