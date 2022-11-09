//
// Created by aminjon on 11/9/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N, W;
    cin >> N >> W;

    vector<int> cost(N + 1, 0), weight(N + 1, 0);
    for (int i = 1; i <= N; ++i) cin >> weight[i];
    for (int i = 1; i <= N; ++i) cin >> cost[i];

    vector<vector<int>> dp(N + 1, vector<int>(W + 1, -1));
    dp[0][0] = 0;
    for (int i = 1; i <= N; ++i) {
        for (int w = 1; w <= W; ++w) {
            dp[i][w] = dp[i - 1][w];
            if (w >= weight[i] && dp[i - 1][w - weight[i]] != -1) {
                dp[i][w] = max(dp[i][w], dp[i - 1][w - weight[i]] + cost[i]);
            }
        }
    }

    cout << *max_element(dp[N].begin(), dp[N].end());
}

int main() {
    solve();
}