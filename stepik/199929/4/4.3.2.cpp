//
// Created by aminjon on 11/9/22.
//
#include <bits/stdc++.h>

using namespace std;

inline constexpr int inf = numeric_limits<int>::max();

auto solve() {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<vector<int>> dp(N + 1, vector<int>(K + 1, inf));
    dp[0][0] = 0;

    for (int i = 1; i <= N; ++i) {
        for (int k = 0; k <= K; ++k) {
            dp[i][k] = dp[i - 1][k];
            if (k >= A[i - 1] && dp[i - 1][k - A[i - 1]] != inf)
                dp[i][k] = min(dp[i][k], dp[i - 1][k - A[i - 1]] + 1);
        }
    }

    int ans = inf;
    for (int i = 0; i <= N; ++i) ans = min(ans, dp[i][K]);
    cout << (ans == inf ? 0 : ans);
}

int main() {
    solve();
}